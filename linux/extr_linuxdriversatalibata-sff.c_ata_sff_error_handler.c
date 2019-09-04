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
struct ata_queued_cmd {int flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  active_tag; } ;
struct ata_port {TYPE_1__* ops; TYPE_2__ link; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/ * ata_reset_fn_t ;
struct TYPE_3__ {int /*<<< orphan*/  postreset; int /*<<< orphan*/  prereset; int /*<<< orphan*/  (* sff_drain_fifo ) (struct ata_queued_cmd*) ;int /*<<< orphan*/ * hardreset; int /*<<< orphan*/ * softreset; } ;

/* Variables and functions */
 int ATA_QCFLAG_FAILED ; 
 struct ata_queued_cmd* __ata_qc_from_tag (struct ata_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_do_eh (struct ata_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sata_scr_valid (TYPE_2__*) ; 
 int /*<<< orphan*/ * sata_sff_hardreset ; 
 int /*<<< orphan*/ * sata_std_hardreset ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct ata_queued_cmd*) ; 

void ata_sff_error_handler(struct ata_port *ap)
{
	ata_reset_fn_t softreset = ap->ops->softreset;
	ata_reset_fn_t hardreset = ap->ops->hardreset;
	struct ata_queued_cmd *qc;
	unsigned long flags;

	qc = __ata_qc_from_tag(ap, ap->link.active_tag);
	if (qc && !(qc->flags & ATA_QCFLAG_FAILED))
		qc = NULL;

	spin_lock_irqsave(ap->lock, flags);

	/*
	 * We *MUST* do FIFO draining before we issue a reset as
	 * several devices helpfully clear their internal state and
	 * will lock solid if we touch the data port post reset. Pass
	 * qc in case anyone wants to do different PIO/DMA recovery or
	 * has per command fixups
	 */
	if (ap->ops->sff_drain_fifo)
		ap->ops->sff_drain_fifo(qc);

	spin_unlock_irqrestore(ap->lock, flags);

	/* ignore built-in hardresets if SCR access is not available */
	if ((hardreset == sata_std_hardreset ||
	     hardreset == sata_sff_hardreset) && !sata_scr_valid(&ap->link))
		hardreset = NULL;

	ata_do_eh(ap, ap->ops->prereset, softreset, hardreset,
		  ap->ops->postreset);
}