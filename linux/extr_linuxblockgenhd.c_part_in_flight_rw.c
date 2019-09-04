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
struct request_queue {scalar_t__ mq_ops; } ;
struct hd_struct {int /*<<< orphan*/ * in_flight; } ;

/* Variables and functions */
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_mq_in_flight_rw (struct request_queue*,struct hd_struct*,unsigned int*) ; 

void part_in_flight_rw(struct request_queue *q, struct hd_struct *part,
		       unsigned int inflight[2])
{
	if (q->mq_ops) {
		blk_mq_in_flight_rw(q, part, inflight);
		return;
	}

	inflight[0] = atomic_read(&part->in_flight[0]);
	inflight[1] = atomic_read(&part->in_flight[1]);
}