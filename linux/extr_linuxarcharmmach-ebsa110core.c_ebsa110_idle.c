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

__attribute__((used)) static void ebsa110_idle(void)
{
	const char *irq_stat = (char *)0xff000000;

	/* disable clock switching */
	asm volatile ("mcr p15, 0, ip, c15, c2, 2" : : : "cc");

	/* wait for an interrupt to occur */
	while (!*irq_stat);

	/* enable clock switching */
	asm volatile ("mcr p15, 0, ip, c15, c1, 2" : : : "cc");
}