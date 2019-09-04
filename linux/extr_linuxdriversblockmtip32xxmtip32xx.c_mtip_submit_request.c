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
struct request {int dummy; } ;
struct mtip_cmd {int /*<<< orphan*/  sg; } ;
struct driver_data {int dd_flag; } ;
struct blk_mq_hw_ctx {TYPE_1__* queue; } ;
struct TYPE_2__ {struct driver_data* queuedata; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
 int ENODATA ; 
 int ENXIO ; 
 int /*<<< orphan*/  MTIP_DDF_OVER_TEMP_BIT ; 
 int /*<<< orphan*/  MTIP_DDF_REBUILD_FAILED_BIT ; 
 int /*<<< orphan*/  MTIP_DDF_REMOVE_PENDING_BIT ; 
 int /*<<< orphan*/  MTIP_DDF_SEC_LOCK_BIT ; 
 int MTIP_DDF_STOP_IO ; 
 int /*<<< orphan*/  MTIP_DDF_WRITE_PROTECT_BIT ; 
 scalar_t__ REQ_OP_DISCARD ; 
 int /*<<< orphan*/  blk_mq_end_request (struct request*,int /*<<< orphan*/ ) ; 
 struct mtip_cmd* blk_mq_rq_to_pdu (struct request*) ; 
 unsigned int blk_rq_map_sg (TYPE_1__*,struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_rq_pos (struct request*) ; 
 int /*<<< orphan*/  blk_rq_sectors (struct request*) ; 
 scalar_t__ is_se_active (struct driver_data*) ; 
 int /*<<< orphan*/  mtip_hw_submit_io (struct driver_data*,struct request*,struct mtip_cmd*,unsigned int,struct blk_mq_hw_ctx*) ; 
 int mtip_send_trim (struct driver_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ req_op (struct request*) ; 
 scalar_t__ rq_data_dir (struct request*) ; 
 int test_bit (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int mtip_submit_request(struct blk_mq_hw_ctx *hctx, struct request *rq)
{
	struct driver_data *dd = hctx->queue->queuedata;
	struct mtip_cmd *cmd = blk_mq_rq_to_pdu(rq);
	unsigned int nents;

	if (is_se_active(dd))
		return -ENODATA;

	if (unlikely(dd->dd_flag & MTIP_DDF_STOP_IO)) {
		if (unlikely(test_bit(MTIP_DDF_REMOVE_PENDING_BIT,
							&dd->dd_flag))) {
			return -ENXIO;
		}
		if (unlikely(test_bit(MTIP_DDF_OVER_TEMP_BIT, &dd->dd_flag))) {
			return -ENODATA;
		}
		if (unlikely(test_bit(MTIP_DDF_WRITE_PROTECT_BIT,
							&dd->dd_flag) &&
				rq_data_dir(rq))) {
			return -ENODATA;
		}
		if (unlikely(test_bit(MTIP_DDF_SEC_LOCK_BIT, &dd->dd_flag) ||
			test_bit(MTIP_DDF_REBUILD_FAILED_BIT, &dd->dd_flag)))
			return -ENODATA;
	}

	if (req_op(rq) == REQ_OP_DISCARD) {
		int err;

		err = mtip_send_trim(dd, blk_rq_pos(rq), blk_rq_sectors(rq));
		blk_mq_end_request(rq, err ? BLK_STS_IOERR : BLK_STS_OK);
		return 0;
	}

	/* Create the scatter list for this request. */
	nents = blk_rq_map_sg(hctx->queue, rq, cmd->sg);

	/* Issue the read/write. */
	mtip_hw_submit_io(dd, rq, cmd, nents, hctx);
	return 0;
}