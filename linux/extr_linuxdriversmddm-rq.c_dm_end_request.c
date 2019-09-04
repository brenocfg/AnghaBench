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
struct request {TYPE_1__* q; struct dm_rq_target_io* end_io_data; } ;
struct mapped_device {int dummy; } ;
struct dm_rq_target_io {TYPE_2__* ti; struct request* orig; struct mapped_device* md; } ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* release_clone_rq ) (struct request*) ;} ;
struct TYPE_5__ {TYPE_3__* type; } ;
struct TYPE_4__ {int /*<<< orphan*/  mq_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_end_request_all (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_end_request (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_rq_unprep_clone (struct request*) ; 
 int /*<<< orphan*/  rq_completed (struct mapped_device*,int,int) ; 
 int rq_data_dir (struct request*) ; 
 int /*<<< orphan*/  rq_end_stats (struct mapped_device*,struct request*) ; 
 int /*<<< orphan*/  stub1 (struct request*) ; 

__attribute__((used)) static void dm_end_request(struct request *clone, blk_status_t error)
{
	int rw = rq_data_dir(clone);
	struct dm_rq_target_io *tio = clone->end_io_data;
	struct mapped_device *md = tio->md;
	struct request *rq = tio->orig;

	blk_rq_unprep_clone(clone);
	tio->ti->type->release_clone_rq(clone);

	rq_end_stats(md, rq);
	if (!rq->q->mq_ops)
		blk_end_request_all(rq, error);
	else
		blk_mq_end_request(rq, error);
	rq_completed(md, rw, true);
}