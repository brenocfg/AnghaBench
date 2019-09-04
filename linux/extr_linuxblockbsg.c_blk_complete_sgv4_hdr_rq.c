#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sg_io_v4 {int dummy; } ;
struct request {TYPE_1__* q; struct request* next_rq; } ;
struct bio {int dummy; } ;
struct TYPE_6__ {int (* complete_rq ) (struct request*,struct sg_io_v4*) ;int /*<<< orphan*/  (* free_rq ) (struct request*) ;} ;
struct TYPE_5__ {TYPE_3__* ops; } ;
struct TYPE_4__ {TYPE_2__ bsg_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_put_request (struct request*) ; 
 int /*<<< orphan*/  blk_rq_unmap_user (struct bio*) ; 
 int stub1 (struct request*,struct sg_io_v4*) ; 
 int /*<<< orphan*/  stub2 (struct request*) ; 

__attribute__((used)) static int blk_complete_sgv4_hdr_rq(struct request *rq, struct sg_io_v4 *hdr,
				    struct bio *bio, struct bio *bidi_bio)
{
	int ret;

	ret = rq->q->bsg_dev.ops->complete_rq(rq, hdr);

	if (rq->next_rq) {
		blk_rq_unmap_user(bidi_bio);
		blk_put_request(rq->next_rq);
	}

	blk_rq_unmap_user(bio);
	rq->q->bsg_dev.ops->free_rq(rq);
	blk_put_request(rq);
	return ret;
}