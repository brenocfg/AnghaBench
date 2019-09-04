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
struct request {int rq_flags; TYPE_1__* q; } ;
struct mapped_device {int dummy; } ;
struct dm_rq_target_io {int /*<<< orphan*/  error; struct mapped_device* md; struct request* clone; } ;
struct TYPE_2__ {int /*<<< orphan*/  mq_ops; } ;

/* Variables and functions */
 int RQF_FAILED ; 
 int /*<<< orphan*/  blk_end_request_all (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_end_request (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_done (struct request*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rq_completed (struct mapped_device*,int,int) ; 
 int rq_data_dir (struct request*) ; 
 int /*<<< orphan*/  rq_end_stats (struct mapped_device*,struct request*) ; 
 struct dm_rq_target_io* tio_from_request (struct request*) ; 

__attribute__((used)) static void dm_softirq_done(struct request *rq)
{
	bool mapped = true;
	struct dm_rq_target_io *tio = tio_from_request(rq);
	struct request *clone = tio->clone;
	int rw;

	if (!clone) {
		struct mapped_device *md = tio->md;

		rq_end_stats(md, rq);
		rw = rq_data_dir(rq);
		if (!rq->q->mq_ops)
			blk_end_request_all(rq, tio->error);
		else
			blk_mq_end_request(rq, tio->error);
		rq_completed(md, rw, false);
		return;
	}

	if (rq->rq_flags & RQF_FAILED)
		mapped = false;

	dm_done(clone, tio->error, mapped);
}