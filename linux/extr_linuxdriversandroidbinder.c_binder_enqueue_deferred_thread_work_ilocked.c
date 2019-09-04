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
struct binder_work {int dummy; } ;
struct binder_thread {int /*<<< orphan*/  todo; } ;

/* Variables and functions */
 int /*<<< orphan*/  binder_enqueue_work_ilocked (struct binder_work*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
binder_enqueue_deferred_thread_work_ilocked(struct binder_thread *thread,
					    struct binder_work *work)
{
	binder_enqueue_work_ilocked(work, &thread->todo);
}