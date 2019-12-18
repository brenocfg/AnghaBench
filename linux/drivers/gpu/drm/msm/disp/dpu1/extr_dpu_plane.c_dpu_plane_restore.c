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
struct drm_plane {int /*<<< orphan*/  state; } ;
struct dpu_plane {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_DEBUG_PLANE (struct dpu_plane*,char*) ; 
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int /*<<< orphan*/  dpu_plane_atomic_update (struct drm_plane*,int /*<<< orphan*/ ) ; 
 struct dpu_plane* to_dpu_plane (struct drm_plane*) ; 

void dpu_plane_restore(struct drm_plane *plane)
{
	struct dpu_plane *pdpu;

	if (!plane || !plane->state) {
		DPU_ERROR("invalid plane\n");
		return;
	}

	pdpu = to_dpu_plane(plane);

	DPU_DEBUG_PLANE(pdpu, "\n");

	/* last plane state is same as current state */
	dpu_plane_atomic_update(plane, plane->state);
}