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
struct intel_gt {int /*<<< orphan*/  pm_notifications; TYPE_1__* i915; int /*<<< orphan*/  wakeref; } ;
struct TYPE_2__ {int /*<<< orphan*/  runtime_pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCKING_INIT_NOTIFIER_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_wakeref_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wf_ops ; 

void intel_gt_pm_init_early(struct intel_gt *gt)
{
	intel_wakeref_init(&gt->wakeref, &gt->i915->runtime_pm, &wf_ops);

	BLOCKING_INIT_NOTIFIER_HEAD(&gt->pm_notifications);
}