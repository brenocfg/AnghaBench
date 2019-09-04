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
typedef  int u32 ;
struct intel_guc {int dummy; } ;
struct guc_ct_buffer_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,int) ; 
 int INTEL_GUC_ACTION_REGISTER_COMMAND_TRANSPORT_BUFFER ; 
 int /*<<< orphan*/  guc_ct_buffer_type_to_str (int) ; 
 int intel_guc_send_mmio (struct intel_guc*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int guc_action_register_ct_buffer(struct intel_guc *guc,
					 u32 desc_addr,
					 u32 type)
{
	u32 action[] = {
		INTEL_GUC_ACTION_REGISTER_COMMAND_TRANSPORT_BUFFER,
		desc_addr,
		sizeof(struct guc_ct_buffer_desc),
		type
	};
	int err;

	/* Can't use generic send(), CT registration must go over MMIO */
	err = intel_guc_send_mmio(guc, action, ARRAY_SIZE(action), NULL, 0);
	if (err)
		DRM_ERROR("CT: register %s buffer failed; err=%d\n",
			  guc_ct_buffer_type_to_str(type), err);
	return err;
}