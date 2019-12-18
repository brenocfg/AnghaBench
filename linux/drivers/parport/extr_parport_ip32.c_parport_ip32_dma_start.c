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
typedef  int /*<<< orphan*/  u64 ;
struct parport {int /*<<< orphan*/  bus_dev; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_6__ {int /*<<< orphan*/  cntlstat; } ;
struct TYPE_7__ {TYPE_1__ parport; } ;
struct TYPE_8__ {TYPE_2__ ctrl; } ;
struct TYPE_10__ {TYPE_3__ perif; } ;
struct TYPE_9__ {int irq_on; int dir; int buf; size_t len; int next; size_t left; scalar_t__ ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DMA_TO_DEVICE ; 
 int /*<<< orphan*/  MACEISA_PAR_CTXA_IRQ ; 
 int /*<<< orphan*/  MACEISA_PAR_CTXB_IRQ ; 
 int MACEPAR_CONTEXT_DATA_BOUND ; 
 int /*<<< orphan*/  MACEPAR_CTLSTAT_DIRECTION ; 
 int /*<<< orphan*/  MACEPAR_CTLSTAT_ENABLE ; 
 int /*<<< orphan*/  MACEPAR_CTLSTAT_RESET ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int dma_map_single (int /*<<< orphan*/ *,void*,size_t,int) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 TYPE_5__* mace ; 
 TYPE_4__ parport_ip32_dma ; 
 int /*<<< orphan*/  parport_ip32_dma_setup_context (int) ; 
 int /*<<< orphan*/  pr_trace (int /*<<< orphan*/ *,char*,int,unsigned long) ; 
 int /*<<< orphan*/  writeq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parport_ip32_dma_start(struct parport *p,
		enum dma_data_direction dir, void *addr, size_t count)
{
	unsigned int limit;
	u64 ctrl;

	pr_trace(NULL, "(%d, %lu)", dir, (unsigned long)count);

	/* FIXME - add support for DMA_FROM_DEVICE.  In this case, buffer must
	 * be 64 bytes aligned. */
	BUG_ON(dir != DMA_TO_DEVICE);

	/* Reset DMA controller */
	ctrl = MACEPAR_CTLSTAT_RESET;
	writeq(ctrl, &mace->perif.ctrl.parport.cntlstat);

	/* DMA IRQs should normally be enabled */
	if (!parport_ip32_dma.irq_on) {
		WARN_ON(1);
		enable_irq(MACEISA_PAR_CTXA_IRQ);
		enable_irq(MACEISA_PAR_CTXB_IRQ);
		parport_ip32_dma.irq_on = 1;
	}

	/* Prepare DMA pointers */
	parport_ip32_dma.dir = dir;
	parport_ip32_dma.buf = dma_map_single(&p->bus_dev, addr, count, dir);
	parport_ip32_dma.len = count;
	parport_ip32_dma.next = parport_ip32_dma.buf;
	parport_ip32_dma.left = parport_ip32_dma.len;
	parport_ip32_dma.ctx = 0;

	/* Setup DMA direction and first two contexts */
	ctrl = (dir == DMA_TO_DEVICE) ? 0 : MACEPAR_CTLSTAT_DIRECTION;
	writeq(ctrl, &mace->perif.ctrl.parport.cntlstat);
	/* Single transfer should not cross a 4K page boundary */
	limit = MACEPAR_CONTEXT_DATA_BOUND -
		(parport_ip32_dma.next & (MACEPAR_CONTEXT_DATA_BOUND - 1));
	parport_ip32_dma_setup_context(limit);
	parport_ip32_dma_setup_context(MACEPAR_CONTEXT_DATA_BOUND);

	/* Real start of DMA transfer */
	ctrl |= MACEPAR_CTLSTAT_ENABLE;
	writeq(ctrl, &mace->perif.ctrl.parport.cntlstat);

	return 0;
}