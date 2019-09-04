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

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 scalar_t__ mm_vc_mem_phys_addr ; 

__attribute__((used)) static inline unsigned int vcaddr_to_pfn(unsigned long vc_addr)
{
	unsigned long pfn = vc_addr & 0x3FFFFFFF;

	pfn += mm_vc_mem_phys_addr;
	pfn >>= PAGE_SHIFT;
	return pfn;
}