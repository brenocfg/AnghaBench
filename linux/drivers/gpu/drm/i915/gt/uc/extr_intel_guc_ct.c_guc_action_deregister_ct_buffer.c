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
struct intel_guc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  INTEL_GUC_ACTION_DEREGISTER_COMMAND_TRANSPORT_BUFFER ; 
 int /*<<< orphan*/  guc_ct_buffer_type_to_str (int /*<<< orphan*/ ) ; 
 int intel_guc_send_mmio (struct intel_guc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int guc_action_deregister_ct_buffer(struct intel_guc *guc,
					   u32 owner,
					   u32 type)
{
	u32 action[] = {
		INTEL_GUC_ACTION_DEREGISTER_COMMAND_TRANSPORT_BUFFER,
		owner,
		type
	};
	int err;

	/* Can't use generic send(), CT deregistration must go over MMIO */
	err = intel_guc_send_mmio(guc, action, ARRAY_SIZE(action), NULL, 0);
	if (err)
		DRM_ERROR("CT: deregister %s buffer failed; owner=%d err=%d\n",
			  guc_ct_buffer_type_to_str(type), owner, err);
	return err;
}