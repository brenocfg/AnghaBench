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
typedef  int /*<<< orphan*/  u32 ;
struct list_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  wait_head; } ;
struct host1x_syncpt {TYPE_1__ intr; int /*<<< orphan*/  id; } ;
struct host1x {int dummy; } ;

/* Variables and functions */
 int HOST1X_INTR_ACTION_COUNT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  host1x_hw_intr_disable_syncpt_intr (struct host1x*,int /*<<< orphan*/ ) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_completed_waiters (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct list_head*) ; 
 int /*<<< orphan*/  reset_threshold_interrupt (struct host1x*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  run_handlers (struct list_head*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int process_wait_list(struct host1x *host,
			     struct host1x_syncpt *syncpt,
			     u32 threshold)
{
	struct list_head completed[HOST1X_INTR_ACTION_COUNT];
	unsigned int i;
	int empty;

	for (i = 0; i < HOST1X_INTR_ACTION_COUNT; ++i)
		INIT_LIST_HEAD(completed + i);

	spin_lock(&syncpt->intr.lock);

	remove_completed_waiters(&syncpt->intr.wait_head, threshold,
				 completed);

	empty = list_empty(&syncpt->intr.wait_head);
	if (empty)
		host1x_hw_intr_disable_syncpt_intr(host, syncpt->id);
	else
		reset_threshold_interrupt(host, &syncpt->intr.wait_head,
					  syncpt->id);

	spin_unlock(&syncpt->intr.lock);

	run_handlers(completed);

	return empty;
}