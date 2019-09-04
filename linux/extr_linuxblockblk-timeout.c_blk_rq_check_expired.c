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
struct request {int /*<<< orphan*/  timeout_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mark_rq_complete (struct request*) ; 
 unsigned long blk_rq_deadline (struct request*) ; 
 int /*<<< orphan*/  blk_rq_timed_out (struct request*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (unsigned long,unsigned long const) ; 
 scalar_t__ time_after_eq (int /*<<< orphan*/ ,unsigned long const) ; 

__attribute__((used)) static void blk_rq_check_expired(struct request *rq, unsigned long *next_timeout,
			  unsigned int *next_set)
{
	const unsigned long deadline = blk_rq_deadline(rq);

	if (time_after_eq(jiffies, deadline)) {
		list_del_init(&rq->timeout_list);

		/*
		 * Check if we raced with end io completion
		 */
		if (!blk_mark_rq_complete(rq))
			blk_rq_timed_out(rq);
	} else if (!*next_set || time_after(*next_timeout, deadline)) {
		*next_timeout = deadline;
		*next_set = 1;
	}
}