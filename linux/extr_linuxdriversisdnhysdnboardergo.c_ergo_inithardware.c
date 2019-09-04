#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  hysdn_lock; int /*<<< orphan*/  irq_queue; int /*<<< orphan*/  set_errlog_state; int /*<<< orphan*/  waitpofready; int /*<<< orphan*/  writebootseq; int /*<<< orphan*/  writebootimg; int /*<<< orphan*/  testram; int /*<<< orphan*/  (* releasehardware ) (TYPE_1__*) ;int /*<<< orphan*/  (* stopcard ) (TYPE_1__*) ;int /*<<< orphan*/  irq; scalar_t__ iobase; scalar_t__ membase; int /*<<< orphan*/  dpram; scalar_t__ memend; } ;
typedef  TYPE_1__ hysdn_card ;

/* Variables and functions */
 scalar_t__ ERG_DPRAM_PAGE_SIZE ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ PCI9050_INTR_REG ; 
 scalar_t__ PCI9050_USER_IO ; 
 int /*<<< orphan*/  ergo_interrupt ; 
 int /*<<< orphan*/  ergo_irq_bh ; 
 int /*<<< orphan*/  ergo_releasehardware (TYPE_1__*) ; 
 int /*<<< orphan*/  ergo_set_errlog_state ; 
 int /*<<< orphan*/  ergo_stopcard (TYPE_1__*) ; 
 int /*<<< orphan*/  ergo_testram ; 
 int /*<<< orphan*/  ergo_waitpofready ; 
 int /*<<< orphan*/  ergo_writebootimg ; 
 int /*<<< orphan*/  ergo_writebootseq ; 
 int /*<<< orphan*/  ioremap (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int) ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  request_region (scalar_t__,int,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int
ergo_inithardware(hysdn_card *card)
{
	if (!request_region(card->iobase + PCI9050_INTR_REG, 1, "HYSDN"))
		return (-1);
	if (!request_region(card->iobase + PCI9050_USER_IO, 1, "HYSDN")) {
		release_region(card->iobase + PCI9050_INTR_REG, 1);
		return (-1);	/* ports already in use */
	}
	card->memend = card->membase + ERG_DPRAM_PAGE_SIZE - 1;
	if (!(card->dpram = ioremap(card->membase, ERG_DPRAM_PAGE_SIZE))) {
		release_region(card->iobase + PCI9050_INTR_REG, 1);
		release_region(card->iobase + PCI9050_USER_IO, 1);
		return (-1);
	}

	ergo_stopcard(card);	/* disable interrupts */
	if (request_irq(card->irq, ergo_interrupt, IRQF_SHARED, "HYSDN", card)) {
		ergo_releasehardware(card); /* return the acquired hardware */
		return (-1);
	}
	/* success, now setup the function pointers */
	card->stopcard = ergo_stopcard;
	card->releasehardware = ergo_releasehardware;
	card->testram = ergo_testram;
	card->writebootimg = ergo_writebootimg;
	card->writebootseq = ergo_writebootseq;
	card->waitpofready = ergo_waitpofready;
	card->set_errlog_state = ergo_set_errlog_state;
	INIT_WORK(&card->irq_queue, ergo_irq_bh);
	spin_lock_init(&card->hysdn_lock);

	return (0);
}