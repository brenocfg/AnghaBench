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
struct hfi_video_work_mode {int /*<<< orphan*/  video_work_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI_PROPERTY_PARAM_WORK_MODE ; 
 int /*<<< orphan*/  IS_V4 (int /*<<< orphan*/ ) ; 
 int hfi_session_set_property (struct venus_inst*,int /*<<< orphan*/  const,struct hfi_video_work_mode*) ; 

int venus_helper_set_work_mode(struct venus_inst *inst, u32 mode)
{
	const u32 ptype = HFI_PROPERTY_PARAM_WORK_MODE;
	struct hfi_video_work_mode wm;

	if (!IS_V4(inst->core))
		return 0;

	wm.video_work_mode = mode;

	return hfi_session_set_property(inst, ptype, &wm);
}