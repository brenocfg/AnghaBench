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
typedef  int /*<<< orphan*/  wait_queue_head_t ;
typedef  int /*<<< orphan*/  wait_queue_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  init_waitqueue_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_timeout (int) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
sleep_timeout_cond(wait_queue_head_t *wait_queue,
		   int *condition,
		   int timeout)
{
	wait_queue_entry_t we;

	init_waitqueue_entry(&we, current);
	add_wait_queue(wait_queue, &we);
	set_current_state(TASK_INTERRUPTIBLE);
	if (!(*condition))
		schedule_timeout(timeout);
	set_current_state(TASK_RUNNING);
	remove_wait_queue(wait_queue, &we);
}