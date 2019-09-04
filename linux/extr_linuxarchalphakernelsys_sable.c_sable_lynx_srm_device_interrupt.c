#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int* mask_to_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  handle_irq (int) ; 
 TYPE_1__* sable_lynx_irq_swizzle ; 

__attribute__((used)) static void 
sable_lynx_srm_device_interrupt(unsigned long vector)
{
	/* Note that the vector reported by the SRM PALcode corresponds
	   to the interrupt mask bits, but we have to manage via the
	   so-called legacy IRQs for many common devices.  */

	int bit, irq;

	bit = (vector - 0x800) >> 4;
	irq = sable_lynx_irq_swizzle->mask_to_irq[bit];
#if 0
	printk("%s: vector 0x%lx bit 0x%x irq 0x%x\n",
	       __func__, vector, bit, irq);
#endif
	handle_irq(irq);
}