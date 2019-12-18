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
struct timer_list {int dummy; } ;
struct gb_operation {int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETIMEDOUT ; 
 struct gb_operation* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_operation_completion_wq ; 
 scalar_t__ gb_operation_result_set (struct gb_operation*,int /*<<< orphan*/ ) ; 
 struct gb_operation* operation ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void gb_operation_timeout(struct timer_list *t)
{
	struct gb_operation *operation = from_timer(operation, t, timer);

	if (gb_operation_result_set(operation, -ETIMEDOUT)) {
		/*
		 * A stuck request message will be cancelled from the
		 * workqueue.
		 */
		queue_work(gb_operation_completion_wq, &operation->work);
	}
}