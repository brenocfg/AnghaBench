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
struct drm_plane {scalar_t__ state; } ;
struct dpu_plane_state {int pending; } ;
struct dpu_plane {int color_fill; scalar_t__ csc_ptr; TYPE_2__* pipe_hw; scalar_t__ is_error; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* setup_csc ) (TYPE_2__*,scalar_t__) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int DPU_PLANE_COLOR_FILL_FLAG ; 
 int /*<<< orphan*/  _dpu_plane_color_fill (struct dpu_plane*,int,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,scalar_t__) ; 
 struct dpu_plane* to_dpu_plane (struct drm_plane*) ; 
 struct dpu_plane_state* to_dpu_plane_state (scalar_t__) ; 

void dpu_plane_flush(struct drm_plane *plane)
{
	struct dpu_plane *pdpu;
	struct dpu_plane_state *pstate;

	if (!plane || !plane->state) {
		DPU_ERROR("invalid plane\n");
		return;
	}

	pdpu = to_dpu_plane(plane);
	pstate = to_dpu_plane_state(plane->state);

	/*
	 * These updates have to be done immediately before the plane flush
	 * timing, and may not be moved to the atomic_update/mode_set functions.
	 */
	if (pdpu->is_error)
		/* force white frame with 100% alpha pipe output on error */
		_dpu_plane_color_fill(pdpu, 0xFFFFFF, 0xFF);
	else if (pdpu->color_fill & DPU_PLANE_COLOR_FILL_FLAG)
		/* force 100% alpha */
		_dpu_plane_color_fill(pdpu, pdpu->color_fill, 0xFF);
	else if (pdpu->pipe_hw && pdpu->csc_ptr && pdpu->pipe_hw->ops.setup_csc)
		pdpu->pipe_hw->ops.setup_csc(pdpu->pipe_hw, pdpu->csc_ptr);

	/* flag h/w flush complete */
	if (plane->state)
		pstate->pending = false;
}