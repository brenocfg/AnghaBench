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
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int guc_clients_create (struct intel_guc*) ; 
 int guc_stage_desc_pool_create (struct intel_guc*) ; 
 int /*<<< orphan*/  guc_stage_desc_pool_destroy (struct intel_guc*) ; 
 int /*<<< orphan*/  guc_verify_doorbells (struct intel_guc*) ; 

int intel_guc_submission_init(struct intel_guc *guc)
{
	int ret;

	if (guc->stage_desc_pool)
		return 0;

	ret = guc_stage_desc_pool_create(guc);
	if (ret)
		return ret;
	/*
	 * Keep static analysers happy, let them know that we allocated the
	 * vma after testing that it didn't exist earlier.
	 */
	GEM_BUG_ON(!guc->stage_desc_pool);

	WARN_ON(!guc_verify_doorbells(guc));
	ret = guc_clients_create(guc);
	if (ret)
		goto err_pool;

	return 0;

err_pool:
	guc_stage_desc_pool_destroy(guc);
	return ret;
}