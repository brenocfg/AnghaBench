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
 int /*<<< orphan*/  local_irq_disable () ; 

__attribute__((used)) static void rng_io_start(void)
{
#ifndef CONFIG_64BIT
	/*
	 * readq is reading a 64-bit register using a 64-bit load.  On
	 * a 32-bit kernel however interrupts or any other processor
	 * exception would clobber the upper 32-bit of the processor
	 * register so interrupts need to be disabled.
	 */
	local_irq_disable();
#endif
}