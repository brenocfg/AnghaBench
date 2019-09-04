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
struct drm_plane {int /*<<< orphan*/  state; } ;
struct dpu_plane_state {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_bitmask_sspp ) (struct dpu_hw_ctl*,int /*<<< orphan*/ ) ;} ;
struct dpu_hw_ctl {TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int /*<<< orphan*/  dpu_plane_pipe (struct drm_plane*) ; 
 int /*<<< orphan*/  stub1 (struct dpu_hw_ctl*,int /*<<< orphan*/ ) ; 
 struct dpu_plane_state* to_dpu_plane_state (int /*<<< orphan*/ ) ; 

void dpu_plane_get_ctl_flush(struct drm_plane *plane, struct dpu_hw_ctl *ctl,
		u32 *flush_sspp)
{
	struct dpu_plane_state *pstate;

	if (!plane || !flush_sspp) {
		DPU_ERROR("invalid parameters\n");
		return;
	}

	pstate = to_dpu_plane_state(plane->state);

	*flush_sspp = ctl->ops.get_bitmask_sspp(ctl, dpu_plane_pipe(plane));
}