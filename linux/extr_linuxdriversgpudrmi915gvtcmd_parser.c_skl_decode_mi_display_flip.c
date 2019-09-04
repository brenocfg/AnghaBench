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
typedef  int u32 ;
struct parser_exec_state {struct intel_vgpu* vgpu; } ;
struct mi_display_flip_command_info {int stride_val; int tile_val; int surf_val; int async_flip; void* pipe; int /*<<< orphan*/  surf_reg; int /*<<< orphan*/  stride_reg; int /*<<< orphan*/  ctrl_reg; void* plane; int /*<<< orphan*/  event; } ;
struct intel_vgpu {TYPE_1__* gvt; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_2__ {struct drm_i915_private* dev_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSPCNTR (void*) ; 
 int /*<<< orphan*/  DSPSTRIDE (void*) ; 
 int /*<<< orphan*/  DSPSURF (void*) ; 
 int EBADRQC ; 
 int GENMASK (int,int) ; 
#define  MI_DISPLAY_FLIP_SKL_PLANE_1_A 133 
#define  MI_DISPLAY_FLIP_SKL_PLANE_1_B 132 
#define  MI_DISPLAY_FLIP_SKL_PLANE_1_C 131 
#define  MI_DISPLAY_FLIP_SKL_PLANE_2_A 130 
#define  MI_DISPLAY_FLIP_SKL_PLANE_2_B 129 
#define  MI_DISPLAY_FLIP_SKL_PLANE_2_C 128 
 void* PIPE_A ; 
 void* PIPE_B ; 
 void* PIPE_C ; 
 int /*<<< orphan*/  PRIMARY_A_FLIP_DONE ; 
 int /*<<< orphan*/  PRIMARY_B_FLIP_DONE ; 
 int /*<<< orphan*/  PRIMARY_C_FLIP_DONE ; 
 void* PRIMARY_PLANE ; 
 int /*<<< orphan*/  SPRITE_A_FLIP_DONE ; 
 int /*<<< orphan*/  SPRITE_B_FLIP_DONE ; 
 int /*<<< orphan*/  SPRITE_C_FLIP_DONE ; 
 void* SPRITE_PLANE ; 
 int cmd_val (struct parser_exec_state*,int) ; 
 int /*<<< orphan*/  gvt_vgpu_err (char*,int) ; 

__attribute__((used)) static int skl_decode_mi_display_flip(struct parser_exec_state *s,
		struct mi_display_flip_command_info *info)
{
	struct drm_i915_private *dev_priv = s->vgpu->gvt->dev_priv;
	struct intel_vgpu *vgpu = s->vgpu;
	u32 dword0 = cmd_val(s, 0);
	u32 dword1 = cmd_val(s, 1);
	u32 dword2 = cmd_val(s, 2);
	u32 plane = (dword0 & GENMASK(12, 8)) >> 8;

	info->plane = PRIMARY_PLANE;

	switch (plane) {
	case MI_DISPLAY_FLIP_SKL_PLANE_1_A:
		info->pipe = PIPE_A;
		info->event = PRIMARY_A_FLIP_DONE;
		break;
	case MI_DISPLAY_FLIP_SKL_PLANE_1_B:
		info->pipe = PIPE_B;
		info->event = PRIMARY_B_FLIP_DONE;
		break;
	case MI_DISPLAY_FLIP_SKL_PLANE_1_C:
		info->pipe = PIPE_C;
		info->event = PRIMARY_C_FLIP_DONE;
		break;

	case MI_DISPLAY_FLIP_SKL_PLANE_2_A:
		info->pipe = PIPE_A;
		info->event = SPRITE_A_FLIP_DONE;
		info->plane = SPRITE_PLANE;
		break;
	case MI_DISPLAY_FLIP_SKL_PLANE_2_B:
		info->pipe = PIPE_B;
		info->event = SPRITE_B_FLIP_DONE;
		info->plane = SPRITE_PLANE;
		break;
	case MI_DISPLAY_FLIP_SKL_PLANE_2_C:
		info->pipe = PIPE_C;
		info->event = SPRITE_C_FLIP_DONE;
		info->plane = SPRITE_PLANE;
		break;

	default:
		gvt_vgpu_err("unknown plane code %d\n", plane);
		return -EBADRQC;
	}

	info->stride_val = (dword1 & GENMASK(15, 6)) >> 6;
	info->tile_val = (dword1 & GENMASK(2, 0));
	info->surf_val = (dword2 & GENMASK(31, 12)) >> 12;
	info->async_flip = ((dword2 & GENMASK(1, 0)) == 0x1);

	info->ctrl_reg = DSPCNTR(info->pipe);
	info->stride_reg = DSPSTRIDE(info->pipe);
	info->surf_reg = DSPSURF(info->pipe);

	return 0;
}