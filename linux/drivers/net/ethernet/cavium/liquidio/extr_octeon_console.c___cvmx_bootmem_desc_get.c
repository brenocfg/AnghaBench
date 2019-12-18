#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  unsigned long long u64 ;
typedef  unsigned long long u32 ;
struct octeon_device {int dummy; } ;

/* Variables and functions */
 unsigned long long octeon_read_device_mem32 (struct octeon_device*,unsigned long long) ; 
 unsigned long long octeon_read_device_mem64 (struct octeon_device*,unsigned long long) ; 

__attribute__((used)) static inline u64 __cvmx_bootmem_desc_get(struct octeon_device *oct,
					  u64 base,
					  u32 offset,
					  u32 size)
{
	base = (1ull << 63) | (base + offset);
	switch (size) {
	case 4:
		return octeon_read_device_mem32(oct, base);
	case 8:
		return octeon_read_device_mem64(oct, base);
	default:
		return 0;
	}
}