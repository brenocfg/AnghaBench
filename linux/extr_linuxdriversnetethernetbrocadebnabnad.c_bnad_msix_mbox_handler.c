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
struct bnad {int /*<<< orphan*/  bna_lock; int /*<<< orphan*/  bna; int /*<<< orphan*/  run_flags; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  BNAD_RF_MBOX_IRQ_DISABLED ; 
 scalar_t__ BNA_IS_MBOX_ERR_INTR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  bna_intr_status_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bna_mbox_handler (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t
bnad_msix_mbox_handler(int irq, void *data)
{
	u32 intr_status;
	unsigned long flags;
	struct bnad *bnad = (struct bnad *)data;

	spin_lock_irqsave(&bnad->bna_lock, flags);
	if (unlikely(test_bit(BNAD_RF_MBOX_IRQ_DISABLED, &bnad->run_flags))) {
		spin_unlock_irqrestore(&bnad->bna_lock, flags);
		return IRQ_HANDLED;
	}

	bna_intr_status_get(&bnad->bna, intr_status);

	if (BNA_IS_MBOX_ERR_INTR(&bnad->bna, intr_status))
		bna_mbox_handler(&bnad->bna, intr_status);

	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	return IRQ_HANDLED;
}