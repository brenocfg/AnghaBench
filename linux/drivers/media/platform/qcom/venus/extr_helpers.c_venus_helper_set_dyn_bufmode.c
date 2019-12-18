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
struct venus_inst {int dummy; } ;
struct hfi_buffer_alloc_mode {int /*<<< orphan*/  type; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI_BUFFER_MODE_DYNAMIC ; 
 int /*<<< orphan*/  HFI_BUFFER_OUTPUT ; 
 int /*<<< orphan*/  HFI_BUFFER_OUTPUT2 ; 
 int /*<<< orphan*/  HFI_PROPERTY_PARAM_BUFFER_ALLOC_MODE ; 
 int hfi_session_set_property (struct venus_inst*,int /*<<< orphan*/  const,struct hfi_buffer_alloc_mode*) ; 
 int /*<<< orphan*/  is_dynamic_bufmode (struct venus_inst*) ; 

int venus_helper_set_dyn_bufmode(struct venus_inst *inst)
{
	const u32 ptype = HFI_PROPERTY_PARAM_BUFFER_ALLOC_MODE;
	struct hfi_buffer_alloc_mode mode;
	int ret;

	if (!is_dynamic_bufmode(inst))
		return 0;

	mode.type = HFI_BUFFER_OUTPUT;
	mode.mode = HFI_BUFFER_MODE_DYNAMIC;

	ret = hfi_session_set_property(inst, ptype, &mode);
	if (ret)
		return ret;

	mode.type = HFI_BUFFER_OUTPUT2;

	return hfi_session_set_property(inst, ptype, &mode);
}