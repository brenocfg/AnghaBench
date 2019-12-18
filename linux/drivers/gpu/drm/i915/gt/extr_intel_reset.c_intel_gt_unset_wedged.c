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
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;
struct intel_gt {TYPE_1__ reset; } ;

/* Variables and functions */
 int __intel_gt_unset_wedged (struct intel_gt*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

bool intel_gt_unset_wedged(struct intel_gt *gt)
{
	bool result;

	mutex_lock(&gt->reset.mutex);
	result = __intel_gt_unset_wedged(gt);
	mutex_unlock(&gt->reset.mutex);

	return result;
}