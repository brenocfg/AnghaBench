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
struct intel_guc {int /*<<< orphan*/  shared_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GUC_POWER_D1 ; 
 int /*<<< orphan*/  INTEL_GUC_ACTION_ENTER_S_STATE ; 
 int /*<<< orphan*/  intel_guc_ggtt_offset (struct intel_guc*,int /*<<< orphan*/ ) ; 
 int intel_guc_send (struct intel_guc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int intel_guc_suspend(struct intel_guc *guc)
{
	u32 data[] = {
		INTEL_GUC_ACTION_ENTER_S_STATE,
		GUC_POWER_D1, /* any value greater than GUC_POWER_D0 */
		intel_guc_ggtt_offset(guc, guc->shared_data)
	};

	return intel_guc_send(guc, data, ARRAY_SIZE(data));
}