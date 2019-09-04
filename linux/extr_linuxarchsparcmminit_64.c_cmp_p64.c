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
struct linux_prom64_registers {scalar_t__ phys_addr; } ;

/* Variables and functions */

__attribute__((used)) static int cmp_p64(const void *a, const void *b)
{
	const struct linux_prom64_registers *x = a, *y = b;

	if (x->phys_addr > y->phys_addr)
		return 1;
	if (x->phys_addr < y->phys_addr)
		return -1;
	return 0;
}