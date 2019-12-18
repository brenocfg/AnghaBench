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
struct intel_timeline {int /*<<< orphan*/  link; int /*<<< orphan*/  active_count; int /*<<< orphan*/  pin_count; int /*<<< orphan*/  mutex; TYPE_1__* gt; } ;
struct intel_gt_timelines {int /*<<< orphan*/  lock; int /*<<< orphan*/  active_list; } ;
struct TYPE_2__ {struct intel_gt_timelines timelines; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void intel_timeline_enter(struct intel_timeline *tl)
{
	struct intel_gt_timelines *timelines = &tl->gt->timelines;
	unsigned long flags;

	lockdep_assert_held(&tl->mutex);

	GEM_BUG_ON(!atomic_read(&tl->pin_count));
	if (tl->active_count++)
		return;
	GEM_BUG_ON(!tl->active_count); /* overflow? */

	spin_lock_irqsave(&timelines->lock, flags);
	list_add(&tl->link, &timelines->active_list);
	spin_unlock_irqrestore(&timelines->lock, flags);
}