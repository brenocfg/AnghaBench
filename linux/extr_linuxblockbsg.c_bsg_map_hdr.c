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
struct sg_io_v4 {char guard; scalar_t__ din_xfer_len; int /*<<< orphan*/  din_xferp; scalar_t__ dout_xfer_len; int /*<<< orphan*/  dout_xferp; int /*<<< orphan*/  timeout; } ;
struct TYPE_4__ {TYPE_1__* ops; int /*<<< orphan*/  class_dev; } ;
struct request_queue {scalar_t__ sg_timeout; TYPE_2__ bsg_dev; int /*<<< orphan*/  queue_flags; } ;
struct request {scalar_t__ timeout; struct request* next_rq; int /*<<< orphan*/  bio; } ;
typedef  int /*<<< orphan*/  fmode_t ;
struct TYPE_3__ {int (* check_proto ) (struct sg_io_v4*) ;int (* fill_hdr ) (struct request*,struct sg_io_v4*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* free_rq ) (struct request*) ;} ;

/* Variables and functions */
 scalar_t__ BLK_DEFAULT_SG_TIMEOUT ; 
 scalar_t__ BLK_MIN_SG_TIMEOUT ; 
 int EINVAL ; 
 int ENXIO ; 
 int EOPNOTSUPP ; 
 struct request* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct request*) ; 
 int PTR_ERR (struct request*) ; 
 int /*<<< orphan*/  QUEUE_FLAG_BIDI ; 
 int /*<<< orphan*/  REQ_OP_SCSI_IN ; 
 int /*<<< orphan*/  REQ_OP_SCSI_OUT ; 
 struct request* blk_get_request (struct request_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_put_request (struct request*) ; 
 int blk_rq_map_user (struct request_queue*,struct request*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_rq_unmap_user (int /*<<< orphan*/ ) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int stub1 (struct sg_io_v4*) ; 
 int stub2 (struct request*,struct sg_io_v4*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct request*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uptr64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct request *
bsg_map_hdr(struct request_queue *q, struct sg_io_v4 *hdr, fmode_t mode)
{
	struct request *rq, *next_rq = NULL;
	int ret;

	if (!q->bsg_dev.class_dev)
		return ERR_PTR(-ENXIO);

	if (hdr->guard != 'Q')
		return ERR_PTR(-EINVAL);

	ret = q->bsg_dev.ops->check_proto(hdr);
	if (ret)
		return ERR_PTR(ret);

	rq = blk_get_request(q, hdr->dout_xfer_len ?
			REQ_OP_SCSI_OUT : REQ_OP_SCSI_IN, 0);
	if (IS_ERR(rq))
		return rq;

	ret = q->bsg_dev.ops->fill_hdr(rq, hdr, mode);
	if (ret)
		goto out;

	rq->timeout = msecs_to_jiffies(hdr->timeout);
	if (!rq->timeout)
		rq->timeout = q->sg_timeout;
	if (!rq->timeout)
		rq->timeout = BLK_DEFAULT_SG_TIMEOUT;
	if (rq->timeout < BLK_MIN_SG_TIMEOUT)
		rq->timeout = BLK_MIN_SG_TIMEOUT;

	if (hdr->dout_xfer_len && hdr->din_xfer_len) {
		if (!test_bit(QUEUE_FLAG_BIDI, &q->queue_flags)) {
			ret = -EOPNOTSUPP;
			goto out;
		}

		next_rq = blk_get_request(q, REQ_OP_SCSI_IN, 0);
		if (IS_ERR(next_rq)) {
			ret = PTR_ERR(next_rq);
			goto out;
		}

		rq->next_rq = next_rq;
		ret = blk_rq_map_user(q, next_rq, NULL, uptr64(hdr->din_xferp),
				       hdr->din_xfer_len, GFP_KERNEL);
		if (ret)
			goto out_free_nextrq;
	}

	if (hdr->dout_xfer_len) {
		ret = blk_rq_map_user(q, rq, NULL, uptr64(hdr->dout_xferp),
				hdr->dout_xfer_len, GFP_KERNEL);
	} else if (hdr->din_xfer_len) {
		ret = blk_rq_map_user(q, rq, NULL, uptr64(hdr->din_xferp),
				hdr->din_xfer_len, GFP_KERNEL);
	}

	if (ret)
		goto out_unmap_nextrq;
	return rq;

out_unmap_nextrq:
	if (rq->next_rq)
		blk_rq_unmap_user(rq->next_rq->bio);
out_free_nextrq:
	if (rq->next_rq)
		blk_put_request(rq->next_rq);
out:
	q->bsg_dev.ops->free_rq(rq);
	blk_put_request(rq);
	return ERR_PTR(ret);
}