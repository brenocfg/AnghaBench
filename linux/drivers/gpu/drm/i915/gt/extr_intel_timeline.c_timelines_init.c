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
struct intel_gt_timelines {int /*<<< orphan*/  hwsp_free_list; int /*<<< orphan*/  hwsp_lock; int /*<<< orphan*/  active_list; int /*<<< orphan*/  lock; } ;
struct intel_gt {struct intel_gt_timelines timelines; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void timelines_init(struct intel_gt *gt)
{
	struct intel_gt_timelines *timelines = &gt->timelines;

	spin_lock_init(&timelines->lock);
	INIT_LIST_HEAD(&timelines->active_list);

	spin_lock_init(&timelines->hwsp_lock);
	INIT_LIST_HEAD(&timelines->hwsp_free_list);
}