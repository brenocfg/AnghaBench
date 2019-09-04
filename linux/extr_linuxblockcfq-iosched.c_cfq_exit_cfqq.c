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
struct cfq_queue {int dummy; } ;
struct cfq_data {struct cfq_queue* active_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cfq_slice_expired (struct cfq_data*,struct cfq_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfq_put_cooperator (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_put_queue (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_schedule_dispatch (struct cfq_data*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void cfq_exit_cfqq(struct cfq_data *cfqd, struct cfq_queue *cfqq)
{
	if (unlikely(cfqq == cfqd->active_queue)) {
		__cfq_slice_expired(cfqd, cfqq, 0);
		cfq_schedule_dispatch(cfqd);
	}

	cfq_put_cooperator(cfqq);

	cfq_put_queue(cfqq);
}