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
struct intel_gt {int /*<<< orphan*/  wakeref; } ;

/* Variables and functions */
 int intel_wakeref_wait_for_idle (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int intel_gt_pm_wait_for_idle(struct intel_gt *gt)
{
	return intel_wakeref_wait_for_idle(&gt->wakeref);
}