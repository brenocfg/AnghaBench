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
struct venus_inst {int /*<<< orphan*/  core; } ;
struct hfi_videocores_usage_type {int /*<<< orphan*/  video_core_enable_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI_PROPERTY_CONFIG_VIDEOCORES_USAGE ; 
 int /*<<< orphan*/  IS_V4 (int /*<<< orphan*/ ) ; 
 int hfi_session_set_property (struct venus_inst*,int /*<<< orphan*/  const,struct hfi_videocores_usage_type*) ; 

int venus_helper_set_core_usage(struct venus_inst *inst, u32 usage)
{
	const u32 ptype = HFI_PROPERTY_CONFIG_VIDEOCORES_USAGE;
	struct hfi_videocores_usage_type cu;

	if (!IS_V4(inst->core))
		return 0;

	cu.video_core_enable_mask = usage;

	return hfi_session_set_property(inst, ptype, &cu);
}