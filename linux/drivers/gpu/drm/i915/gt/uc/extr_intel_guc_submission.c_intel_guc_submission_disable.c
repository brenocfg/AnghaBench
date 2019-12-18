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
struct intel_guc {int dummy; } ;
struct intel_gt {int /*<<< orphan*/  awake; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  guc_clients_disable (struct intel_guc*) ; 
 int /*<<< orphan*/  guc_interrupts_release (struct intel_gt*) ; 
 struct intel_gt* guc_to_gt (struct intel_guc*) ; 

void intel_guc_submission_disable(struct intel_guc *guc)
{
	struct intel_gt *gt = guc_to_gt(guc);

	GEM_BUG_ON(gt->awake); /* GT should be parked first */

	guc_interrupts_release(gt);
	guc_clients_disable(guc);
}