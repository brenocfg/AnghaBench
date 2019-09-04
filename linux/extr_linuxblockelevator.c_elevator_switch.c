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
struct request_queue {struct elevator_queue* elevator; scalar_t__ mq_ops; int /*<<< orphan*/  sysfs_lock; } ;
struct TYPE_3__ {int (* elevator_init_fn ) (struct request_queue*,struct elevator_type*) ;} ;
struct TYPE_4__ {TYPE_1__ sq; } ;
struct elevator_type {int /*<<< orphan*/  elevator_name; TYPE_2__ ops; } ;
struct elevator_queue {int registered; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_add_trace_msg (struct request_queue*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_freeze_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_mq_quiesce_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_mq_unfreeze_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_mq_unquiesce_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_bypass_end (struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_bypass_start (struct request_queue*) ; 
 int /*<<< orphan*/  elevator_exit (struct request_queue*,struct elevator_queue*) ; 
 int elevator_switch_mq (struct request_queue*,struct elevator_type*) ; 
 int elv_register_queue (struct request_queue*) ; 
 int /*<<< orphan*/  elv_unregister_queue (struct request_queue*) ; 
 int /*<<< orphan*/  ioc_clear_queue (struct request_queue*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int stub1 (struct request_queue*,struct elevator_type*) ; 

__attribute__((used)) static int elevator_switch(struct request_queue *q, struct elevator_type *new_e)
{
	struct elevator_queue *old = q->elevator;
	bool old_registered = false;
	int err;

	lockdep_assert_held(&q->sysfs_lock);

	if (q->mq_ops) {
		blk_mq_freeze_queue(q);
		blk_mq_quiesce_queue(q);

		err = elevator_switch_mq(q, new_e);

		blk_mq_unquiesce_queue(q);
		blk_mq_unfreeze_queue(q);

		return err;
	}

	/*
	 * Turn on BYPASS and drain all requests w/ elevator private data.
	 * Block layer doesn't call into a quiesced elevator - all requests
	 * are directly put on the dispatch list without elevator data
	 * using INSERT_BACK.  All requests have SOFTBARRIER set and no
	 * merge happens either.
	 */
	if (old) {
		old_registered = old->registered;

		blk_queue_bypass_start(q);

		/* unregister and clear all auxiliary data of the old elevator */
		if (old_registered)
			elv_unregister_queue(q);

		ioc_clear_queue(q);
	}

	/* allocate, init and register new elevator */
	err = new_e->ops.sq.elevator_init_fn(q, new_e);
	if (err)
		goto fail_init;

	err = elv_register_queue(q);
	if (err)
		goto fail_register;

	/* done, kill the old one and finish */
	if (old) {
		elevator_exit(q, old);
		blk_queue_bypass_end(q);
	}

	blk_add_trace_msg(q, "elv switch: %s", new_e->elevator_name);

	return 0;

fail_register:
	elevator_exit(q, q->elevator);
fail_init:
	/* switch failed, restore and re-register old elevator */
	if (old) {
		q->elevator = old;
		elv_register_queue(q);
		blk_queue_bypass_end(q);
	}

	return err;
}