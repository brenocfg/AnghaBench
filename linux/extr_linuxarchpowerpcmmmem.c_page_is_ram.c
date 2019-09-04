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
 int /*<<< orphan*/  __pfn_to_phys (unsigned long) ; 
 int memblock_is_memory (int /*<<< orphan*/ ) ; 

int page_is_ram(unsigned long pfn)
{
	return memblock_is_memory(__pfn_to_phys(pfn));
}