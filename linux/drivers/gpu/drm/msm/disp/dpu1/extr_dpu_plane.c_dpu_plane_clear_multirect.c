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
struct drm_plane_state {int dummy; } ;
struct dpu_plane_state {int /*<<< orphan*/  multirect_mode; int /*<<< orphan*/  multirect_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_SSPP_MULTIRECT_NONE ; 
 int /*<<< orphan*/  DPU_SSPP_RECT_SOLO ; 
 struct dpu_plane_state* to_dpu_plane_state (struct drm_plane_state const*) ; 

void dpu_plane_clear_multirect(const struct drm_plane_state *drm_state)
{
	struct dpu_plane_state *pstate = to_dpu_plane_state(drm_state);

	pstate->multirect_index = DPU_SSPP_RECT_SOLO;
	pstate->multirect_mode = DPU_SSPP_MULTIRECT_NONE;
}