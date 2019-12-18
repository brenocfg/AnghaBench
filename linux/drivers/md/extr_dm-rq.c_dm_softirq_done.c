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
struct request {int rq_flags; } ;
struct mapped_device {int dummy; } ;
struct dm_rq_target_io {int /*<<< orphan*/  error; struct mapped_device* md; struct request* clone; } ;

/* Variables and functions */
 int RQF_FAILED ; 
 int /*<<< orphan*/  blk_mq_end_request (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_done (struct request*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rq_completed (struct mapped_device*) ; 
 int /*<<< orphan*/  rq_end_stats (struct mapped_device*,struct request*) ; 
 struct dm_rq_target_io* tio_from_request (struct request*) ; 

__attribute__((used)) static void dm_softirq_done(struct request *rq)
{
	bool mapped = true;
	struct dm_rq_target_io *tio = tio_from_request(rq);
	struct request *clone = tio->clone;

	if (!clone) {
		struct mapped_device *md = tio->md;

		rq_end_stats(md, rq);
		blk_mq_end_request(rq, tio->error);
		rq_completed(md);
		return;
	}

	if (rq->rq_flags & RQF_FAILED)
		mapped = false;

	dm_done(clone, tio->error, mapped);
}