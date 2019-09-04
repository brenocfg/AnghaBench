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
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PTE_VALID ; 
 int __change_memory_common (unsigned long,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __pgprot (int /*<<< orphan*/ ) ; 

int set_memory_valid(unsigned long addr, int numpages, int enable)
{
	if (enable)
		return __change_memory_common(addr, PAGE_SIZE * numpages,
					__pgprot(PTE_VALID),
					__pgprot(0));
	else
		return __change_memory_common(addr, PAGE_SIZE * numpages,
					__pgprot(0),
					__pgprot(PTE_VALID));
}