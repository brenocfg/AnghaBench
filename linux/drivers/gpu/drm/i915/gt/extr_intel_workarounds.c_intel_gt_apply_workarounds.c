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
struct intel_gt {TYPE_1__* i915; int /*<<< orphan*/  uncore; } ;
struct TYPE_2__ {int /*<<< orphan*/  gt_wa_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  wa_list_apply (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void intel_gt_apply_workarounds(struct intel_gt *gt)
{
	wa_list_apply(gt->uncore, &gt->i915->gt_wa_list);
}