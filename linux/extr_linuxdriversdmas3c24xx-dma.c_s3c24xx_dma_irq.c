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
struct TYPE_10__ {TYPE_4__* next; } ;
struct s3c24xx_txd {TYPE_5__ dsg_list; TYPE_4__* at; int /*<<< orphan*/  vd; scalar_t__ cyclic; } ;
struct s3c24xx_dma_phy {int /*<<< orphan*/  id; TYPE_2__* host; struct s3c24xx_dma_chan* serving; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
struct s3c24xx_dma_chan {TYPE_3__ vc; struct s3c24xx_txd* at; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_9__ {struct TYPE_9__* next; } ;
struct TYPE_7__ {TYPE_1__* pdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_is_last (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  s3c24xx_dma_phy_free (struct s3c24xx_dma_chan*) ; 
 int /*<<< orphan*/  s3c24xx_dma_start_next_sg (struct s3c24xx_dma_chan*,struct s3c24xx_txd*) ; 
 int /*<<< orphan*/  s3c24xx_dma_start_next_txd (struct s3c24xx_dma_chan*) ; 
 int /*<<< orphan*/  s3c24xx_dma_terminate_phy (struct s3c24xx_dma_phy*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vchan_cookie_complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_cyclic_callback (int /*<<< orphan*/ *) ; 
 scalar_t__ vchan_next_desc (TYPE_3__*) ; 

__attribute__((used)) static irqreturn_t s3c24xx_dma_irq(int irq, void *data)
{
	struct s3c24xx_dma_phy *phy = data;
	struct s3c24xx_dma_chan *s3cchan = phy->serving;
	struct s3c24xx_txd *txd;

	dev_dbg(&phy->host->pdev->dev, "interrupt on channel %d\n", phy->id);

	/*
	 * Interrupts happen to notify the completion of a transfer and the
	 * channel should have moved into its stop state already on its own.
	 * Therefore interrupts on channels not bound to a virtual channel
	 * should never happen. Nevertheless send a terminate command to the
	 * channel if the unlikely case happens.
	 */
	if (unlikely(!s3cchan)) {
		dev_err(&phy->host->pdev->dev, "interrupt on unused channel %d\n",
			phy->id);

		s3c24xx_dma_terminate_phy(phy);

		return IRQ_HANDLED;
	}

	spin_lock(&s3cchan->vc.lock);
	txd = s3cchan->at;
	if (txd) {
		/* when more sg's are in this txd, start the next one */
		if (!list_is_last(txd->at, &txd->dsg_list)) {
			txd->at = txd->at->next;
			if (txd->cyclic)
				vchan_cyclic_callback(&txd->vd);
			s3c24xx_dma_start_next_sg(s3cchan, txd);
		} else if (!txd->cyclic) {
			s3cchan->at = NULL;
			vchan_cookie_complete(&txd->vd);

			/*
			 * And start the next descriptor (if any),
			 * otherwise free this channel.
			 */
			if (vchan_next_desc(&s3cchan->vc))
				s3c24xx_dma_start_next_txd(s3cchan);
			else
				s3c24xx_dma_phy_free(s3cchan);
		} else {
			vchan_cyclic_callback(&txd->vd);

			/* Cyclic: reset at beginning */
			txd->at = txd->dsg_list.next;
			s3c24xx_dma_start_next_sg(s3cchan, txd);
		}
	}
	spin_unlock(&s3cchan->vc.lock);

	return IRQ_HANDLED;
}