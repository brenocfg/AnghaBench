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

__attribute__((used)) static inline bool is_hypervisor_range(int idx)
{
#ifdef CONFIG_X86_64
	/*
	 * A hole in the beginning of kernel address space reserved
	 * for a hypervisor.
	 */
	return	(idx >= pgd_index(GUARD_HOLE_BASE_ADDR)) &&
		(idx <  pgd_index(GUARD_HOLE_END_ADDR));
#else
	return false;
#endif
}