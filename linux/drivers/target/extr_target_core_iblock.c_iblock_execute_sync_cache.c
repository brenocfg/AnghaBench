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
struct se_cmd {int* t_task_cdb; int /*<<< orphan*/  se_dev; } ;
struct iblock_dev {int /*<<< orphan*/  ibd_bd; } ;
struct bio {int bi_opf; struct se_cmd* bi_private; int /*<<< orphan*/  bi_end_io; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct iblock_dev* IBLOCK_DEV (int /*<<< orphan*/ ) ; 
 int REQ_OP_WRITE ; 
 int REQ_PREFLUSH ; 
 int /*<<< orphan*/  SAM_STAT_GOOD ; 
 struct bio* bio_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iblock_end_io_flush ; 
 int /*<<< orphan*/  submit_bio (struct bio*) ; 
 int /*<<< orphan*/  target_complete_cmd (struct se_cmd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static sense_reason_t
iblock_execute_sync_cache(struct se_cmd *cmd)
{
	struct iblock_dev *ib_dev = IBLOCK_DEV(cmd->se_dev);
	int immed = (cmd->t_task_cdb[1] & 0x2);
	struct bio *bio;

	/*
	 * If the Immediate bit is set, queue up the GOOD response
	 * for this SYNCHRONIZE_CACHE op.
	 */
	if (immed)
		target_complete_cmd(cmd, SAM_STAT_GOOD);

	bio = bio_alloc(GFP_KERNEL, 0);
	bio->bi_end_io = iblock_end_io_flush;
	bio_set_dev(bio, ib_dev->ibd_bd);
	bio->bi_opf = REQ_OP_WRITE | REQ_PREFLUSH;
	if (!immed)
		bio->bi_private = cmd;
	submit_bio(bio);
	return 0;
}