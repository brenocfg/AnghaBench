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
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 unsigned long PHYS_PFN (int /*<<< orphan*/ ) ; 
 unsigned long SUBSECTION_ALIGN_DOWN (unsigned long) ; 

__attribute__((used)) static unsigned long init_altmap_base(resource_size_t base)
{
	unsigned long base_pfn = PHYS_PFN(base);

	return SUBSECTION_ALIGN_DOWN(base_pfn);
}