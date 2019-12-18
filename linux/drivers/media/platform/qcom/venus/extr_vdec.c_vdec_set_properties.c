#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct vdec_controls {scalar_t__ post_loop_deb_mode; } ;
struct TYPE_2__ {struct vdec_controls dec; } ;
struct venus_inst {TYPE_1__ controls; } ;
struct hfi_enable {int enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI_PROPERTY_CONFIG_VDEC_POST_LOOP_DEBLOCKER ; 
 int hfi_session_set_property (struct venus_inst*,int /*<<< orphan*/ ,struct hfi_enable*) ; 

__attribute__((used)) static int vdec_set_properties(struct venus_inst *inst)
{
	struct vdec_controls *ctr = &inst->controls.dec;
	struct hfi_enable en = { .enable = 1 };
	u32 ptype;
	int ret;

	if (ctr->post_loop_deb_mode) {
		ptype = HFI_PROPERTY_CONFIG_VDEC_POST_LOOP_DEBLOCKER;
		ret = hfi_session_set_property(inst, ptype, &en);
		if (ret)
			return ret;
	}

	return 0;
}