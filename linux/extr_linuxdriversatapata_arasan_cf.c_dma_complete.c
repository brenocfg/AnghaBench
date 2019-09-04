#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  protocol; } ;
struct ata_queued_cmd {TYPE_3__* ap; TYPE_1__ tf; int /*<<< orphan*/  err_mask; } ;
struct arasan_cf_dev {TYPE_4__* host; int /*<<< orphan*/  irq; struct ata_queued_cmd* qc; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  eh_info; } ;
struct TYPE_7__ {TYPE_2__ link; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_ehi_push_desc (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ata_is_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_sff_interrupt (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void dma_complete(struct arasan_cf_dev *acdev)
{
	struct ata_queued_cmd *qc = acdev->qc;
	unsigned long flags;

	acdev->qc = NULL;
	ata_sff_interrupt(acdev->irq, acdev->host);

	spin_lock_irqsave(&acdev->host->lock, flags);
	if (unlikely(qc->err_mask) && ata_is_dma(qc->tf.protocol))
		ata_ehi_push_desc(&qc->ap->link.eh_info, "DMA Failed: Timeout");
	spin_unlock_irqrestore(&acdev->host->lock, flags);
}