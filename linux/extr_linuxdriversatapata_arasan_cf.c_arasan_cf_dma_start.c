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
typedef  int u32 ;
struct ata_taskfile {int flags; } ;
struct ata_queued_cmd {struct ata_taskfile tf; struct ata_port* ap; } ;
struct ata_port {TYPE_1__* ops; } ;
struct arasan_cf_dev {int /*<<< orphan*/  work; scalar_t__ vbase; struct ata_queued_cmd* qc; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* sff_exec_command ) (struct ata_port*,struct ata_taskfile*) ;} ;

/* Variables and functions */
 int ATA_TFLAG_WRITE ; 
 scalar_t__ XFER_CTR ; 
 int XFER_DIR_MASK ; 
 int XFER_READ ; 
 int XFER_WRITE ; 
 int /*<<< orphan*/  ata_sff_queue_work (int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct ata_port*,struct ata_taskfile*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void arasan_cf_dma_start(struct arasan_cf_dev *acdev)
{
	struct ata_queued_cmd *qc = acdev->qc;
	struct ata_port *ap = qc->ap;
	struct ata_taskfile *tf = &qc->tf;
	u32 xfer_ctr = readl(acdev->vbase + XFER_CTR) & ~XFER_DIR_MASK;
	u32 write = tf->flags & ATA_TFLAG_WRITE;

	xfer_ctr |= write ? XFER_WRITE : XFER_READ;
	writel(xfer_ctr, acdev->vbase + XFER_CTR);

	ap->ops->sff_exec_command(ap, tf);
	ata_sff_queue_work(&acdev->work);
}