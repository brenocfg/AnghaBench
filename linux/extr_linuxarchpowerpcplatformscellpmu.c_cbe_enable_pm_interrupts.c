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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  cbe_write_pm (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  iic_set_interrupt_routing (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_status ; 

void cbe_enable_pm_interrupts(u32 cpu, u32 thread, u32 mask)
{
	/* Set which node and thread will handle the next interrupt. */
	iic_set_interrupt_routing(cpu, thread, 0);

	/* Enable the interrupt bits in the pm_status register. */
	if (mask)
		cbe_write_pm(cpu, pm_status, mask);
}