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
struct msm_gem_address_space {int dummy; } ;
struct drm_plane {int dummy; } ;
struct drm_framebuffer {int dummy; } ;
struct dpu_plane_state {int /*<<< orphan*/  multirect_index; } ;
struct dpu_plane {TYPE_2__* pipe_hw; } ;
struct dpu_hw_pipe_cfg {int /*<<< orphan*/  layout; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* setup_sourceaddress ) (TYPE_2__*,struct dpu_hw_pipe_cfg*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ ops; int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_DEBUG_PLANE (struct dpu_plane*,char*) ; 
 int /*<<< orphan*/  DPU_ERROR (char*,int,int,int,int) ; 
 int /*<<< orphan*/  DPU_ERROR_PLANE (struct dpu_plane*,char*,...) ; 
 int EAGAIN ; 
 int _dpu_plane_get_aspace (struct dpu_plane*,struct dpu_plane_state*,struct msm_gem_address_space**) ; 
 int dpu_format_populate_layout (struct msm_gem_address_space*,struct drm_framebuffer*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,struct dpu_hw_pipe_cfg*,int /*<<< orphan*/ ) ; 
 struct dpu_plane* to_dpu_plane (struct drm_plane*) ; 
 int /*<<< orphan*/  trace_dpu_plane_set_scanout (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void _dpu_plane_set_scanout(struct drm_plane *plane,
		struct dpu_plane_state *pstate,
		struct dpu_hw_pipe_cfg *pipe_cfg,
		struct drm_framebuffer *fb)
{
	struct dpu_plane *pdpu;
	struct msm_gem_address_space *aspace = NULL;
	int ret;

	if (!plane || !pstate || !pipe_cfg || !fb) {
		DPU_ERROR(
			"invalid arg(s), plane %d state %d cfg %d fb %d\n",
			plane != 0, pstate != 0, pipe_cfg != 0, fb != 0);
		return;
	}

	pdpu = to_dpu_plane(plane);
	if (!pdpu->pipe_hw) {
		DPU_ERROR_PLANE(pdpu, "invalid pipe_hw\n");
		return;
	}

	ret = _dpu_plane_get_aspace(pdpu, pstate, &aspace);
	if (ret) {
		DPU_ERROR_PLANE(pdpu, "Failed to get aspace %d\n", ret);
		return;
	}

	ret = dpu_format_populate_layout(aspace, fb, &pipe_cfg->layout);
	if (ret == -EAGAIN)
		DPU_DEBUG_PLANE(pdpu, "not updating same src addrs\n");
	else if (ret)
		DPU_ERROR_PLANE(pdpu, "failed to get format layout, %d\n", ret);
	else if (pdpu->pipe_hw->ops.setup_sourceaddress) {
		trace_dpu_plane_set_scanout(pdpu->pipe_hw->idx,
					    &pipe_cfg->layout,
					    pstate->multirect_index);
		pdpu->pipe_hw->ops.setup_sourceaddress(pdpu->pipe_hw, pipe_cfg,
						pstate->multirect_index);
	}
}