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
typedef  size_t u32 ;
struct guc_policy {int dummy; } ;
struct guc_policies {int is_valid; struct guc_policy** policy; int /*<<< orphan*/  max_num_work_items; int /*<<< orphan*/  dpc_promote_time; } ;

/* Variables and functions */
 size_t GUC_CLIENT_PRIORITY_NUM ; 
 size_t GUC_MAX_ENGINE_CLASSES ; 
 int /*<<< orphan*/  POLICY_DEFAULT_DPC_PROMOTE_TIME_US ; 
 int /*<<< orphan*/  POLICY_MAX_NUM_WI ; 
 int /*<<< orphan*/  guc_policy_init (struct guc_policy*) ; 

__attribute__((used)) static void guc_policies_init(struct guc_policies *policies)
{
	struct guc_policy *policy;
	u32 p, i;

	policies->dpc_promote_time = POLICY_DEFAULT_DPC_PROMOTE_TIME_US;
	policies->max_num_work_items = POLICY_MAX_NUM_WI;

	for (p = 0; p < GUC_CLIENT_PRIORITY_NUM; p++) {
		for (i = 0; i < GUC_MAX_ENGINE_CLASSES; i++) {
			policy = &policies->policy[p][i];

			guc_policy_init(policy);
		}
	}

	policies->is_valid = 1;
}