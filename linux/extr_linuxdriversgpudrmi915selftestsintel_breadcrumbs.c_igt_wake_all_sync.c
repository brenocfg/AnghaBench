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
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wait_var_event (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void igt_wake_all_sync(atomic_t *ready,
			      atomic_t *set,
			      atomic_t *done,
			      wait_queue_head_t *wq,
			      int count)
{
	atomic_set(set, count);
	atomic_set(ready, 0);
	wake_up_all(wq);

	wait_var_event(set, !atomic_read(set));
	atomic_set(ready, count);
	atomic_set(done, count);
}