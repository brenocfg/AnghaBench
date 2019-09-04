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
typedef  scalar_t__ phys_addr_t ;

/* Variables and functions */
 scalar_t__ ARC_UNCACHED_ADDR_SPACE ; 
 scalar_t__ is_isa_arcompact () ; 
 scalar_t__ perip_base ; 
 scalar_t__ perip_end ; 

__attribute__((used)) static inline bool arc_uncached_addr_space(phys_addr_t paddr)
{
	if (is_isa_arcompact()) {
		if (paddr >= ARC_UNCACHED_ADDR_SPACE)
			return true;
	} else if (paddr >= perip_base && paddr <= perip_end) {
		return true;
	}

	return false;
}