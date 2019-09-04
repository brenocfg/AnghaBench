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
struct getcpu_cache {int dummy; } ;

/* Variables and functions */

long
__vdso_getcpu(unsigned *cpu, unsigned *node, struct getcpu_cache *unused)
{
	/*
	 * UML does not support SMP, we can cheat here. :)
	 */

	if (cpu)
		*cpu = 0;
	if (node)
		*node = 0;

	return 0;
}