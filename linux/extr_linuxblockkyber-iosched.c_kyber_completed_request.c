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
typedef  scalar_t__ u64 ;
struct request_queue {TYPE_1__* elevator; } ;
struct request {scalar_t__ io_start_time_ns; int /*<<< orphan*/  cmd_flags; struct request_queue* q; } ;
struct kyber_queue_data {scalar_t__ read_lat_nsec; scalar_t__ write_lat_nsec; int /*<<< orphan*/  cb; } ;
struct TYPE_2__ {struct kyber_queue_data* elevator_data; } ;

/* Variables and functions */
#define  KYBER_READ 129 
#define  KYBER_SYNC_WRITE 128 
 int /*<<< orphan*/  blk_stat_activate_msecs (int /*<<< orphan*/ ,int) ; 
 scalar_t__ blk_stat_is_active (int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_get_ns () ; 
 unsigned int kyber_sched_domain (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kyber_completed_request(struct request *rq)
{
	struct request_queue *q = rq->q;
	struct kyber_queue_data *kqd = q->elevator->elevator_data;
	unsigned int sched_domain;
	u64 now, latency, target;

	/*
	 * Check if this request met our latency goal. If not, quickly gather
	 * some statistics and start throttling.
	 */
	sched_domain = kyber_sched_domain(rq->cmd_flags);
	switch (sched_domain) {
	case KYBER_READ:
		target = kqd->read_lat_nsec;
		break;
	case KYBER_SYNC_WRITE:
		target = kqd->write_lat_nsec;
		break;
	default:
		return;
	}

	/* If we are already monitoring latencies, don't check again. */
	if (blk_stat_is_active(kqd->cb))
		return;

	now = ktime_get_ns();
	if (now < rq->io_start_time_ns)
		return;

	latency = now - rq->io_start_time_ns;

	if (latency > target)
		blk_stat_activate_msecs(kqd->cb, 10);
}