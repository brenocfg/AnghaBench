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
struct intel_gt {int dummy; } ;
typedef  int /*<<< orphan*/  intel_engine_mask_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_ENGINES ; 
 int RESET_MAX_RETRIES ; 
 int __intel_gt_reset (struct intel_gt*,int /*<<< orphan*/ ) ; 
 int gt_reset (struct intel_gt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gt_revoke (struct intel_gt*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int do_reset(struct intel_gt *gt, intel_engine_mask_t stalled_mask)
{
	int err, i;

	gt_revoke(gt);

	err = __intel_gt_reset(gt, ALL_ENGINES);
	for (i = 0; err && i < RESET_MAX_RETRIES; i++) {
		msleep(10 * (i + 1));
		err = __intel_gt_reset(gt, ALL_ENGINES);
	}
	if (err)
		return err;

	return gt_reset(gt, stalled_mask);
}