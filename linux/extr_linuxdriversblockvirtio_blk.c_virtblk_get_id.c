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
struct virtio_blk {TYPE_1__* disk; } ;
struct request_queue {int dummy; } ;
struct request {int dummy; } ;
struct gendisk {struct virtio_blk* private_data; } ;
struct TYPE_2__ {struct request_queue* queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct request*) ; 
 int PTR_ERR (struct request*) ; 
 int /*<<< orphan*/  REQ_OP_DRV_IN ; 
 int /*<<< orphan*/  VIRTIO_BLK_ID_BYTES ; 
 int /*<<< orphan*/  blk_execute_rq (struct request_queue*,TYPE_1__*,struct request*,int) ; 
 struct request* blk_get_request (struct request_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  blk_put_request (struct request*) ; 
 int blk_rq_map_kern (struct request_queue*,struct request*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int blk_status_to_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtblk_result (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int virtblk_get_id(struct gendisk *disk, char *id_str)
{
	struct virtio_blk *vblk = disk->private_data;
	struct request_queue *q = vblk->disk->queue;
	struct request *req;
	int err;

	req = blk_get_request(q, REQ_OP_DRV_IN, 0);
	if (IS_ERR(req))
		return PTR_ERR(req);

	err = blk_rq_map_kern(q, req, id_str, VIRTIO_BLK_ID_BYTES, GFP_KERNEL);
	if (err)
		goto out;

	blk_execute_rq(vblk->disk->queue, vblk->disk, req, false);
	err = blk_status_to_errno(virtblk_result(blk_mq_rq_to_pdu(req)));
out:
	blk_put_request(req);
	return err;
}