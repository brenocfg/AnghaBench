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
struct request {scalar_t__ fifo_time; } ;
struct deadline_data {TYPE_1__* fifo_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 struct request* rq_entry_fifo (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after_eq (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static inline int deadline_check_fifo(struct deadline_data *dd, int ddir)
{
	struct request *rq = rq_entry_fifo(dd->fifo_list[ddir].next);

	/*
	 * rq is expired!
	 */
	if (time_after_eq(jiffies, (unsigned long)rq->fifo_time))
		return 1;

	return 0;
}