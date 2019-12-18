#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  cntlstat; } ;
struct TYPE_7__ {TYPE_1__ parport; } ;
struct TYPE_8__ {TYPE_2__ ctrl; } ;
struct TYPE_10__ {TYPE_3__ perif; } ;
struct TYPE_9__ {int irq_on; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MACEISA_PAR_CTXA_IRQ ; 
 int /*<<< orphan*/  MACEISA_PAR_CTXB_IRQ ; 
 int /*<<< orphan*/  MACEISA_PAR_MERR_IRQ ; 
 int /*<<< orphan*/  MACEPAR_CTLSTAT_RESET ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_5__* mace ; 
 TYPE_4__ parport_ip32_dma ; 
 int /*<<< orphan*/  parport_ip32_dma_interrupt ; 
 int /*<<< orphan*/  parport_ip32_merr_interrupt ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parport_ip32_dma_register(void)
{
	int err;

	spin_lock_init(&parport_ip32_dma.lock);
	parport_ip32_dma.irq_on = 1;

	/* Reset DMA controller */
	writeq(MACEPAR_CTLSTAT_RESET, &mace->perif.ctrl.parport.cntlstat);

	/* Request IRQs */
	err = request_irq(MACEISA_PAR_CTXA_IRQ, parport_ip32_dma_interrupt,
			  0, "parport_ip32", NULL);
	if (err)
		goto fail_a;
	err = request_irq(MACEISA_PAR_CTXB_IRQ, parport_ip32_dma_interrupt,
			  0, "parport_ip32", NULL);
	if (err)
		goto fail_b;
#if DEBUG_PARPORT_IP32
	/* FIXME - what is this IRQ for? */
	err = request_irq(MACEISA_PAR_MERR_IRQ, parport_ip32_merr_interrupt,
			  0, "parport_ip32", NULL);
	if (err)
		goto fail_merr;
#endif
	return 0;

#if DEBUG_PARPORT_IP32
fail_merr:
	free_irq(MACEISA_PAR_CTXB_IRQ, NULL);
#endif
fail_b:
	free_irq(MACEISA_PAR_CTXA_IRQ, NULL);
fail_a:
	return err;
}