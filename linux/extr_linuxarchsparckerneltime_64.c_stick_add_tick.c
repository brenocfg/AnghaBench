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

__attribute__((used)) static unsigned long stick_add_tick(unsigned long adj)
{
	unsigned long new_tick;

	__asm__ __volatile__("rd	%%asr24, %0\n\t"
			     "add	%0, %1, %0\n\t"
			     "wr	%0, 0, %%asr24\n\t"
			     : "=&r" (new_tick)
			     : "r" (adj));

	return new_tick;
}