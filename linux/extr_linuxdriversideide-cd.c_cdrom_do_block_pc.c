#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request_queue {unsigned int dma_pad_mask; } ;
struct request {scalar_t__ bio; int /*<<< orphan*/  rq_flags; int /*<<< orphan*/  cmd_type; int /*<<< orphan*/ * cmd; } ;
struct TYPE_3__ {int dma; int dev_flags; struct request_queue* queue; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  IDE_DBG_PC ; 
 int IDE_DFLAG_USING_DMA ; 
 int /*<<< orphan*/  RQF_FAILED ; 
 int /*<<< orphan*/  RQF_QUIET ; 
 char* bio_data (scalar_t__) ; 
 int blk_rq_bytes (struct request*) ; 
 scalar_t__ blk_rq_is_scsi (struct request*) ; 
 int /*<<< orphan*/  ide_debug_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ object_is_on_stack (char*) ; 
 unsigned int queue_dma_alignment (struct request_queue*) ; 

__attribute__((used)) static void cdrom_do_block_pc(ide_drive_t *drive, struct request *rq)
{

	ide_debug_log(IDE_DBG_PC, "rq->cmd[0]: 0x%x, rq->cmd_type: 0x%x",
				  rq->cmd[0], rq->cmd_type);

	if (blk_rq_is_scsi(rq))
		rq->rq_flags |= RQF_QUIET;
	else
		rq->rq_flags &= ~RQF_FAILED;

	drive->dma = 0;

	/* sg request */
	if (rq->bio) {
		struct request_queue *q = drive->queue;
		char *buf = bio_data(rq->bio);
		unsigned int alignment;

		drive->dma = !!(drive->dev_flags & IDE_DFLAG_USING_DMA);

		/*
		 * check if dma is safe
		 *
		 * NOTE! The "len" and "addr" checks should possibly have
		 * separate masks.
		 */
		alignment = queue_dma_alignment(q) | q->dma_pad_mask;
		if ((unsigned long)buf & alignment
		    || blk_rq_bytes(rq) & q->dma_pad_mask
		    || object_is_on_stack(buf))
			drive->dma = 0;
	}
}