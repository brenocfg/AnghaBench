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
struct request_queue {struct elevator_queue* elevator; } ;
struct elevator_queue {struct cfq_data* elevator_data; } ;
struct cfq_data {scalar_t__ cfq_slice_idle; } ;

/* Variables and functions */
 scalar_t__ blk_queue_nonrot (struct request_queue*) ; 
 int /*<<< orphan*/  wbt_disable_default (struct request_queue*) ; 

__attribute__((used)) static void cfq_registered_queue(struct request_queue *q)
{
	struct elevator_queue *e = q->elevator;
	struct cfq_data *cfqd = e->elevator_data;

	/*
	 * Default to IOPS mode with no idling for SSDs
	 */
	if (blk_queue_nonrot(q))
		cfqd->cfq_slice_idle = 0;
	wbt_disable_default(q);
}