#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct bnad {int cfg_flags; int /*<<< orphan*/  mbox_irq_name; int /*<<< orphan*/  run_flags; int /*<<< orphan*/  bna_lock; TYPE_2__* pcidev; TYPE_1__* msix_table; } ;
typedef  scalar_t__ irq_handler_t ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;
struct TYPE_3__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int BNAD_CF_MSIX ; 
 size_t BNAD_MAILBOX_MSIX_INDEX ; 
 char* BNAD_NAME ; 
 int /*<<< orphan*/  BNAD_RF_MBOX_IRQ_DISABLED ; 
 int /*<<< orphan*/  BNAD_UPDATE_CTR (struct bnad*,int /*<<< orphan*/ ) ; 
 unsigned long IRQF_SHARED ; 
 scalar_t__ bnad_isr ; 
 scalar_t__ bnad_msix_mbox_handler ; 
 int /*<<< orphan*/  mbox_intr_disabled ; 
 int request_irq (int /*<<< orphan*/ ,scalar_t__,unsigned long,int /*<<< orphan*/ ,struct bnad*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int
bnad_mbox_irq_alloc(struct bnad *bnad)
{
	int		err = 0;
	unsigned long	irq_flags, flags;
	u32	irq;
	irq_handler_t	irq_handler;

	spin_lock_irqsave(&bnad->bna_lock, flags);
	if (bnad->cfg_flags & BNAD_CF_MSIX) {
		irq_handler = (irq_handler_t)bnad_msix_mbox_handler;
		irq = bnad->msix_table[BNAD_MAILBOX_MSIX_INDEX].vector;
		irq_flags = 0;
	} else {
		irq_handler = (irq_handler_t)bnad_isr;
		irq = bnad->pcidev->irq;
		irq_flags = IRQF_SHARED;
	}

	spin_unlock_irqrestore(&bnad->bna_lock, flags);
	sprintf(bnad->mbox_irq_name, "%s", BNAD_NAME);

	/*
	 * Set the Mbox IRQ disable flag, so that the IRQ handler
	 * called from request_irq() for SHARED IRQs do not execute
	 */
	set_bit(BNAD_RF_MBOX_IRQ_DISABLED, &bnad->run_flags);

	BNAD_UPDATE_CTR(bnad, mbox_intr_disabled);

	err = request_irq(irq, irq_handler, irq_flags,
			  bnad->mbox_irq_name, bnad);

	return err;
}