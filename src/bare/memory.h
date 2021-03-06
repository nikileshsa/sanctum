#if !defined(BARE_MEMORY_H_INCLUDED)
#define BARE_MEMORY_H_INCLUDED

#include "base_types.h"
#include "phys_ptr.h"

namespace sanctum {
namespace bare {

// Sets the DMARBASE (DMA range base) register in the DMA master.
//
// This can only be called by the security monitor.
void set_dmar_base(uintptr_t value);

// Sets the DMARMASK (DMA range mask) register in the DMA master.
//
// This can only be called by the security monitor.
void set_dmar_mask(uintptr_t value);

// Obtains the DRAM size from the memory subsystem.
//
// The implementation may be very slow, so the return value should be cached.
//
// The implementation may use privileged instructions.
size_t read_dram_size();

// The number of levels of cache memory.
//
// The implementation may be very slow, so the return value should be cached.
//
// The implementation may use privileged instructions.
size_t read_cache_levels();

// True if the given cache level is shared among cores.
//
// The implementation may be very slow, so the return value should be cached.
//
// The implementation may use privileged instructions.
bool is_shared_cache(size_t cache_level);

// The size of a cache line at a given level.
//
// The implementation may be very slow, so the return value should be cached.
//
// The implementation may use privileged instructions.
size_t read_cache_line_size(size_t cache_level);

// The number of cache sets at a given level.
//
// The implementation may be very slow, so the return value should be cached.
//
// The implementation may use privileged instructions.
size_t read_cache_set_count(size_t cache_level);

// The maximum value of the cache index shift for the platform.
size_t read_min_cache_index_shift();

// The minimum value of the cache index shift for the platform.
size_t read_max_cache_index_shift();

// Fills a buffer in physical memory with zeros.
//
// In order to allow for optimized assembly implementations, both the starting
// address and buffer size must be a multiple of the cache line size.
template<typename T> void bzero(phys_ptr<T> start, size_t bytes);

// Copies data between two non-overlaping buffers in physical memory.
//
// In order to allow for optimized assembly implementations, both addresses, as
// well as the buffer size must be a multiple of the cache line size.
template<typename T> void bcopy(phys_ptr<T> dest, phys_ptr<T> source,
    size_t bytes);

};  // namespace sanctum::bare
};  // namespace sanctum

// Per-architecture implementations of memory operations.
#include "memory_arch.h"

#endif  // !defined(BARE_MEMORY_H_INCLUDED)
