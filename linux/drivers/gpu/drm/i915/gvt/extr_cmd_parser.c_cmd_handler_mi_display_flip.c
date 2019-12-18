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
struct parser_exec_state {struct intel_vgpu* vgpu; } ;
struct mi_display_flip_command_info {int dummy; } ;
struct intel_vgpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_LEN (int) ; 
 int DWORD_FIELD (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MI_NOOP ; 
 int check_mi_display_flip (struct parser_exec_state*,struct mi_display_flip_command_info*) ; 
 int cmd_length (struct parser_exec_state*) ; 
 int /*<<< orphan*/  cmd_ptr (struct parser_exec_state*,int) ; 
 int decode_mi_display_flip (struct parser_exec_state*,struct mi_display_flip_command_info*) ; 
 int gvt_check_valid_cmd_length (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gvt_vgpu_err (char*) ; 
 int /*<<< orphan*/  patch_value (struct parser_exec_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int update_plane_mmio_from_mi_display_flip (struct parser_exec_state*,struct mi_display_flip_command_info*) ; 

__attribute__((used)) static int cmd_handler_mi_display_flip(struct parser_exec_state *s)
{
	struct mi_display_flip_command_info info;
	struct intel_vgpu *vgpu = s->vgpu;
	int ret;
	int i;
	int len = cmd_length(s);
	u32 valid_len = CMD_LEN(1);

	/* Flip Type == Stereo 3D Flip */
	if (DWORD_FIELD(2, 1, 0) == 2)
		valid_len++;
	ret = gvt_check_valid_cmd_length(cmd_length(s),
			valid_len);
	if (ret)
		return ret;

	ret = decode_mi_display_flip(s, &info);
	if (ret) {
		gvt_vgpu_err("fail to decode MI display flip command\n");
		return ret;
	}

	ret = check_mi_display_flip(s, &info);
	if (ret) {
		gvt_vgpu_err("invalid MI display flip command\n");
		return ret;
	}

	ret = update_plane_mmio_from_mi_display_flip(s, &info);
	if (ret) {
		gvt_vgpu_err("fail to update plane mmio\n");
		return ret;
	}

	for (i = 0; i < len; i++)
		patch_value(s, cmd_ptr(s, i), MI_NOOP);
	return 0;
}