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
struct intel_guc {scalar_t__ stage_desc_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  guc_clients_destroy (struct intel_guc*) ; 
 int /*<<< orphan*/  guc_stage_desc_pool_destroy (struct intel_guc*) ; 
 int /*<<< orphan*/  guc_verify_doorbells (struct intel_guc*) ; 

void intel_guc_submission_fini(struct intel_guc *guc)
{
	guc_clients_destroy(guc);
	WARN_ON(!guc_verify_doorbells(guc));

	if (guc->stage_desc_pool)
		guc_stage_desc_pool_destroy(guc);
}