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
struct TYPE_2__ {scalar_t__ (* process_interrupt_regs ) (struct octeon_device*) ;int /*<<< orphan*/  (* enable_interrupt ) (struct octeon_device*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* disable_interrupt ) (struct octeon_device*,int /*<<< orphan*/ ) ;} ;
struct octeon_device {TYPE_1__ fn_list; int /*<<< orphan*/  status; } ;
typedef  scalar_t__ irqreturn_t ;

/* Variables and functions */
 scalar_t__ IRQ_HANDLED ; 
 int /*<<< orphan*/  OCTEON_ALL_INTR ; 
 scalar_t__ OCT_DEV_IN_RESET ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  liquidio_schedule_droq_pkt_handlers (struct octeon_device*) ; 
 int /*<<< orphan*/  stub1 (struct octeon_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (struct octeon_device*) ; 
 int /*<<< orphan*/  stub3 (struct octeon_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
irqreturn_t liquidio_legacy_intr_handler(int irq __attribute__((unused)),
					 void *dev)
{
	struct octeon_device *oct = (struct octeon_device *)dev;
	irqreturn_t ret;

	/* Disable our interrupts for the duration of ISR */
	oct->fn_list.disable_interrupt(oct, OCTEON_ALL_INTR);

	ret = oct->fn_list.process_interrupt_regs(oct);

	if (ret == IRQ_HANDLED)
		liquidio_schedule_droq_pkt_handlers(oct);

	/* Re-enable our interrupts  */
	if (!(atomic_read(&oct->status) == OCT_DEV_IN_RESET))
		oct->fn_list.enable_interrupt(oct, OCTEON_ALL_INTR);

	return ret;
}