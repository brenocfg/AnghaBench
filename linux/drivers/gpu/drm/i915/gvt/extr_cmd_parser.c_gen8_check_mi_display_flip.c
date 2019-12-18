#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct parser_exec_state {TYPE_2__* vgpu; } ;
struct mi_display_flip_command_info {int stride_val; int tile_val; int /*<<< orphan*/  ctrl_reg; int /*<<< orphan*/  stride_reg; int /*<<< orphan*/  async_flip; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_4__ {TYPE_1__* gvt; } ;
struct TYPE_3__ {struct drm_i915_private* dev_priv; } ;

/* Variables and functions */
 int GENMASK (int,int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gvt_dbg_cmd (char*) ; 
 int vgpu_vreg_t (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gen8_check_mi_display_flip(struct parser_exec_state *s,
		struct mi_display_flip_command_info *info)
{
	struct drm_i915_private *dev_priv = s->vgpu->gvt->dev_priv;
	u32 stride, tile;

	if (!info->async_flip)
		return 0;

	if (INTEL_GEN(dev_priv) >= 9) {
		stride = vgpu_vreg_t(s->vgpu, info->stride_reg) & GENMASK(9, 0);
		tile = (vgpu_vreg_t(s->vgpu, info->ctrl_reg) &
				GENMASK(12, 10)) >> 10;
	} else {
		stride = (vgpu_vreg_t(s->vgpu, info->stride_reg) &
				GENMASK(15, 6)) >> 6;
		tile = (vgpu_vreg_t(s->vgpu, info->ctrl_reg) & (1 << 10)) >> 10;
	}

	if (stride != info->stride_val)
		gvt_dbg_cmd("cannot change stride during async flip\n");

	if (tile != info->tile_val)
		gvt_dbg_cmd("cannot change tile during async flip\n");

	return 0;
}