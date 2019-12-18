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
struct request {int dummy; } ;
struct mapped_device {int dummy; } ;
struct dm_rq_target_io {scalar_t__ clone; TYPE_2__* ti; struct request* orig; struct mapped_device* md; } ;
struct TYPE_4__ {TYPE_1__* type; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* release_clone_rq ) (scalar_t__,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  blk_rq_unprep_clone (scalar_t__) ; 
 int /*<<< orphan*/  dm_mq_delay_requeue_request (struct request*,unsigned long) ; 
 int /*<<< orphan*/  rq_completed (struct mapped_device*) ; 
 int /*<<< orphan*/  rq_end_stats (struct mapped_device*,struct request*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dm_requeue_original_request(struct dm_rq_target_io *tio, bool delay_requeue)
{
	struct mapped_device *md = tio->md;
	struct request *rq = tio->orig;
	unsigned long delay_ms = delay_requeue ? 100 : 0;

	rq_end_stats(md, rq);
	if (tio->clone) {
		blk_rq_unprep_clone(tio->clone);
		tio->ti->type->release_clone_rq(tio->clone, NULL);
	}

	dm_mq_delay_requeue_request(rq, delay_ms);
	rq_completed(md);
}