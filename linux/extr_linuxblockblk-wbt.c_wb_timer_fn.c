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
struct TYPE_4__ {TYPE_1__* q; } ;
struct rq_depth {scalar_t__ scale_step; } ;
struct rq_wb {int /*<<< orphan*/  unknown_cnt; TYPE_2__ rqos; struct rq_depth rq_depth; } ;
struct blk_stat_callback {int /*<<< orphan*/  stat; struct rq_wb* data; } ;
struct TYPE_3__ {int /*<<< orphan*/  backing_dev_info; } ;

/* Variables and functions */
#define  LAT_EXCEEDED 131 
#define  LAT_OK 130 
#define  LAT_UNKNOWN 129 
#define  LAT_UNKNOWN_WRITES 128 
 int /*<<< orphan*/  RWB_UNKNOWN_BUMP ; 
 int latency_exceeded (struct rq_wb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rwb_arm_timer (struct rq_wb*) ; 
 int /*<<< orphan*/  scale_down (struct rq_wb*,int) ; 
 int /*<<< orphan*/  scale_up (struct rq_wb*) ; 
 int /*<<< orphan*/  trace_wbt_timer (int /*<<< orphan*/ ,int,scalar_t__,unsigned int) ; 
 unsigned int wbt_inflight (struct rq_wb*) ; 

__attribute__((used)) static void wb_timer_fn(struct blk_stat_callback *cb)
{
	struct rq_wb *rwb = cb->data;
	struct rq_depth *rqd = &rwb->rq_depth;
	unsigned int inflight = wbt_inflight(rwb);
	int status;

	status = latency_exceeded(rwb, cb->stat);

	trace_wbt_timer(rwb->rqos.q->backing_dev_info, status, rqd->scale_step,
			inflight);

	/*
	 * If we exceeded the latency target, step down. If we did not,
	 * step one level up. If we don't know enough to say either exceeded
	 * or ok, then don't do anything.
	 */
	switch (status) {
	case LAT_EXCEEDED:
		scale_down(rwb, true);
		break;
	case LAT_OK:
		scale_up(rwb);
		break;
	case LAT_UNKNOWN_WRITES:
		/*
		 * We started a the center step, but don't have a valid
		 * read/write sample, but we do have writes going on.
		 * Allow step to go negative, to increase write perf.
		 */
		scale_up(rwb);
		break;
	case LAT_UNKNOWN:
		if (++rwb->unknown_cnt < RWB_UNKNOWN_BUMP)
			break;
		/*
		 * We get here when previously scaled reduced depth, and we
		 * currently don't have a valid read/write sample. For that
		 * case, slowly return to center state (step == 0).
		 */
		if (rqd->scale_step > 0)
			scale_up(rwb);
		else if (rqd->scale_step < 0)
			scale_down(rwb, false);
		break;
	default:
		break;
	}

	/*
	 * Re-arm timer, if we have IO in flight
	 */
	if (rqd->scale_step || inflight)
		rwb_arm_timer(rwb);
}