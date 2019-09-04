#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct msix_entry {int dummy; } ;
struct bnad {int cfg_flags; int msix_num; int /*<<< orphan*/  bna_lock; TYPE_3__* msix_table; TYPE_1__* pcidev; } ;
struct TYPE_8__ {int entry; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BNAD_CF_MSIX ; 
 int BNAD_MAILBOX_MSIX_VECTORS ; 
 int BNAD_NUM_RXP ; 
 int BNAD_NUM_TXQ ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bnad_q_num_adjust (struct bnad*,int,int) ; 
 int /*<<< orphan*/  bnad_q_num_init (struct bnad*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_3__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 int /*<<< orphan*/  pci_disable_msix (TYPE_1__*) ; 
 int pci_enable_msix_range (TYPE_1__*,TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  pci_intx (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
bnad_enable_msix(struct bnad *bnad)
{
	int i, ret;
	unsigned long flags;

	spin_lock_irqsave(&bnad->bna_lock, flags);
	if (!(bnad->cfg_flags & BNAD_CF_MSIX)) {
		spin_unlock_irqrestore(&bnad->bna_lock, flags);
		return;
	}
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	if (bnad->msix_table)
		return;

	bnad->msix_table =
		kcalloc(bnad->msix_num, sizeof(struct msix_entry), GFP_KERNEL);

	if (!bnad->msix_table)
		goto intx_mode;

	for (i = 0; i < bnad->msix_num; i++)
		bnad->msix_table[i].entry = i;

	ret = pci_enable_msix_range(bnad->pcidev, bnad->msix_table,
				    1, bnad->msix_num);
	if (ret < 0) {
		goto intx_mode;
	} else if (ret < bnad->msix_num) {
		dev_warn(&bnad->pcidev->dev,
			 "%d MSI-X vectors allocated < %d requested\n",
			 ret, bnad->msix_num);

		spin_lock_irqsave(&bnad->bna_lock, flags);
		/* ret = #of vectors that we got */
		bnad_q_num_adjust(bnad, (ret - BNAD_MAILBOX_MSIX_VECTORS) / 2,
			(ret - BNAD_MAILBOX_MSIX_VECTORS) / 2);
		spin_unlock_irqrestore(&bnad->bna_lock, flags);

		bnad->msix_num = BNAD_NUM_TXQ + BNAD_NUM_RXP +
			 BNAD_MAILBOX_MSIX_VECTORS;

		if (bnad->msix_num > ret) {
			pci_disable_msix(bnad->pcidev);
			goto intx_mode;
		}
	}

	pci_intx(bnad->pcidev, 0);

	return;

intx_mode:
	dev_warn(&bnad->pcidev->dev,
		 "MSI-X enable failed - operating in INTx mode\n");

	kfree(bnad->msix_table);
	bnad->msix_table = NULL;
	bnad->msix_num = 0;
	spin_lock_irqsave(&bnad->bna_lock, flags);
	bnad->cfg_flags &= ~BNAD_CF_MSIX;
	bnad_q_num_init(bnad);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);
}