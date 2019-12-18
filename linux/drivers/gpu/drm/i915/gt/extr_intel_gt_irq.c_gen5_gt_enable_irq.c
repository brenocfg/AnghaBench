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
typedef  int /*<<< orphan*/  u32 ;
struct intel_gt {int /*<<< orphan*/  uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  GTIMR ; 
 int /*<<< orphan*/  gen5_gt_update_irq (struct intel_gt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_posting_read_fw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void gen5_gt_enable_irq(struct intel_gt *gt, u32 mask)
{
	gen5_gt_update_irq(gt, mask, mask);
	intel_uncore_posting_read_fw(gt->uncore, GTIMR);
}