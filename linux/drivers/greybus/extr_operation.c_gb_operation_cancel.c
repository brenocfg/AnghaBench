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
struct gb_operation {int /*<<< orphan*/  waiters; int /*<<< orphan*/  request; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gb_message_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_operation_cancellation_queue ; 
 int /*<<< orphan*/  gb_operation_completion_wq ; 
 int /*<<< orphan*/  gb_operation_is_active (struct gb_operation*) ; 
 int /*<<< orphan*/  gb_operation_is_incoming (struct gb_operation*) ; 
 scalar_t__ gb_operation_result_set (struct gb_operation*,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_gb_message_cancel_outgoing (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void gb_operation_cancel(struct gb_operation *operation, int errno)
{
	if (WARN_ON(gb_operation_is_incoming(operation)))
		return;

	if (gb_operation_result_set(operation, errno)) {
		gb_message_cancel(operation->request);
		queue_work(gb_operation_completion_wq, &operation->work);
	}
	trace_gb_message_cancel_outgoing(operation->request);

	atomic_inc(&operation->waiters);
	wait_event(gb_operation_cancellation_queue,
		   !gb_operation_is_active(operation));
	atomic_dec(&operation->waiters);
}