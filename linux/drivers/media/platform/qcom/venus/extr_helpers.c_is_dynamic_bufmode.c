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
struct venus_inst {int /*<<< orphan*/  session_type; int /*<<< orphan*/  hfi_codec; struct venus_core* core; } ;
struct venus_core {int dummy; } ;
struct venus_caps {int cap_bufs_mode_dynamic; } ;

/* Variables and functions */
 scalar_t__ IS_V4 (struct venus_core*) ; 
 struct venus_caps* venus_caps_by_codec (struct venus_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_dynamic_bufmode(struct venus_inst *inst)
{
	struct venus_core *core = inst->core;
	struct venus_caps *caps;

	/*
	 * v4 doesn't send BUFFER_ALLOC_MODE_SUPPORTED property and supports
	 * dynamic buffer mode by default for HFI_BUFFER_OUTPUT/OUTPUT2.
	 */
	if (IS_V4(core))
		return true;

	caps = venus_caps_by_codec(core, inst->hfi_codec, inst->session_type);
	if (!caps)
		return false;

	return caps->cap_bufs_mode_dynamic;
}