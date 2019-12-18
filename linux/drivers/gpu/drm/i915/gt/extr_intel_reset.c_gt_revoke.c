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

/* Variables and functions */
 int /*<<< orphan*/  revoke_mmaps (struct intel_gt*) ; 

__attribute__((used)) static void gt_revoke(struct intel_gt *gt)
{
	revoke_mmaps(gt);
}