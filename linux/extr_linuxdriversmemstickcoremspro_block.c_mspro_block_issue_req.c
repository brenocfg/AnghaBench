#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct mspro_block_data {scalar_t__ data_dir; TYPE_1__* block_req; int /*<<< orphan*/  queue; int /*<<< orphan*/  transfer_cmd; int /*<<< orphan*/  (* setup_transfer ) (struct memstick_dev*,int,unsigned int) ;int /*<<< orphan*/  seg_count; int /*<<< orphan*/  req_sg; scalar_t__ current_seg; scalar_t__ current_page; } ;
struct memstick_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  host; } ;
struct TYPE_7__ {int /*<<< orphan*/  q; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_RESOURCE ; 
 int EAGAIN ; 
 int /*<<< orphan*/  MSPRO_CMD_READ_DATA ; 
 int /*<<< orphan*/  MSPRO_CMD_WRITE_DATA ; 
 scalar_t__ READ ; 
 int __blk_end_request_cur (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* blk_fetch_request (int /*<<< orphan*/ ) ; 
 unsigned int blk_rq_bytes (TYPE_1__*) ; 
 int /*<<< orphan*/  blk_rq_map_sg (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int blk_rq_pos (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct mspro_block_data* memstick_get_drvdata (struct memstick_dev*) ; 
 int /*<<< orphan*/  memstick_new_req (int /*<<< orphan*/ ) ; 
 scalar_t__ rq_data_dir (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (struct memstick_dev*,int,unsigned int) ; 

__attribute__((used)) static int mspro_block_issue_req(struct memstick_dev *card, int chunk)
{
	struct mspro_block_data *msb = memstick_get_drvdata(card);
	u64 t_off;
	unsigned int count;

try_again:
	while (chunk) {
		msb->current_page = 0;
		msb->current_seg = 0;
		msb->seg_count = blk_rq_map_sg(msb->block_req->q,
					       msb->block_req,
					       msb->req_sg);

		if (!msb->seg_count) {
			chunk = __blk_end_request_cur(msb->block_req,
					BLK_STS_RESOURCE);
			continue;
		}

		t_off = blk_rq_pos(msb->block_req);
		t_off <<= 9;
		count = blk_rq_bytes(msb->block_req);

		msb->setup_transfer(card, t_off, count);

		msb->data_dir = rq_data_dir(msb->block_req);
		msb->transfer_cmd = msb->data_dir == READ
				    ? MSPRO_CMD_READ_DATA
				    : MSPRO_CMD_WRITE_DATA;

		memstick_new_req(card->host);
		return 0;
	}

	dev_dbg(&card->dev, "blk_fetch\n");
	msb->block_req = blk_fetch_request(msb->queue);
	if (!msb->block_req) {
		dev_dbg(&card->dev, "issue end\n");
		return -EAGAIN;
	}

	dev_dbg(&card->dev, "trying again\n");
	chunk = 1;
	goto try_again;
}