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
struct mspro_block_data {scalar_t__ data_dir; int current_seg; unsigned int page_size; int current_page; int /*<<< orphan*/  q_lock; int /*<<< orphan*/ * block_req; TYPE_2__* req_sg; } ;
struct TYPE_3__ {scalar_t__ tpc; } ;
struct memstick_dev {int /*<<< orphan*/  mrq_complete; int /*<<< orphan*/  next_request; int /*<<< orphan*/  dev; TYPE_1__ current_mrq; } ;
struct TYPE_4__ {unsigned int length; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ MSPRO_CMD_STOP ; 
 scalar_t__ READ ; 
 int /*<<< orphan*/  __blk_mq_end_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int blk_rq_bytes (int /*<<< orphan*/ *) ; 
 unsigned int blk_rq_cur_bytes (int /*<<< orphan*/ *) ; 
 int blk_update_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned int,int) ; 
 int /*<<< orphan*/  errno_to_blk_status (int) ; 
 int /*<<< orphan*/  h_mspro_block_default_bad ; 
 struct mspro_block_data* memstick_get_drvdata (struct memstick_dev*) ; 
 int mspro_block_issue_req (struct memstick_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int mspro_block_complete_req(struct memstick_dev *card, int error)
{
	struct mspro_block_data *msb = memstick_get_drvdata(card);
	int cnt;
	bool chunk;
	unsigned int t_len = 0;
	unsigned long flags;

	spin_lock_irqsave(&msb->q_lock, flags);
	dev_dbg(&card->dev, "complete %d, %d\n", msb->block_req ? 1 : 0,
		error);

	if (msb->block_req) {
		/* Nothing to do - not really an error */
		if (error == -EAGAIN)
			error = 0;

		if (error || (card->current_mrq.tpc == MSPRO_CMD_STOP)) {
			if (msb->data_dir == READ) {
				for (cnt = 0; cnt < msb->current_seg; cnt++) {
					t_len += msb->req_sg[cnt].length
						 / msb->page_size;

					if (msb->current_page)
						t_len += msb->current_page - 1;

					t_len *= msb->page_size;
				}
			}
		} else
			t_len = blk_rq_bytes(msb->block_req);

		dev_dbg(&card->dev, "transferred %x (%d)\n", t_len, error);

		if (error && !t_len)
			t_len = blk_rq_cur_bytes(msb->block_req);

		chunk = blk_update_request(msb->block_req,
				errno_to_blk_status(error), t_len);
		if (chunk) {
			error = mspro_block_issue_req(card);
			if (!error)
				goto out;
		} else {
			__blk_mq_end_request(msb->block_req,
						errno_to_blk_status(error));
			msb->block_req = NULL;
		}
	} else {
		if (!error)
			error = -EAGAIN;
	}

	card->next_request = h_mspro_block_default_bad;
	complete_all(&card->mrq_complete);
out:
	spin_unlock_irqrestore(&msb->q_lock, flags);
	return error;
}