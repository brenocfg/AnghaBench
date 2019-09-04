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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_NOAUTOEN ; 
 int cookie_build_irq (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_status_flags (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun4v_virq ; 

unsigned int sun4v_build_virq(u32 devhandle, unsigned int devino)
{
	int irq;

	irq = cookie_build_irq(devhandle, devino, &sun4v_virq);
	if (!irq)
		goto out;

	/* This is borrowed from the original function.
	 */
	irq_set_status_flags(irq, IRQ_NOAUTOEN);

out:
	return irq;
}