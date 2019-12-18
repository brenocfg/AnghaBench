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
struct drm_plane {int dummy; } ;
struct dpu_plane {int /*<<< orphan*/  pipe_hw; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_DEBUG_PLANE (struct dpu_plane*,char*) ; 
 int /*<<< orphan*/  DPU_PLANE_QOS_PANIC_CTRL ; 
 int /*<<< orphan*/  _dpu_plane_set_qos_ctrl (struct drm_plane*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpu_hw_sspp_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_plane_cleanup (struct drm_plane*) ; 
 int /*<<< orphan*/  kfree (struct dpu_plane*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct dpu_plane* to_dpu_plane (struct drm_plane*) ; 

__attribute__((used)) static void dpu_plane_destroy(struct drm_plane *plane)
{
	struct dpu_plane *pdpu = plane ? to_dpu_plane(plane) : NULL;

	DPU_DEBUG_PLANE(pdpu, "\n");

	if (pdpu) {
		_dpu_plane_set_qos_ctrl(plane, false, DPU_PLANE_QOS_PANIC_CTRL);

		mutex_destroy(&pdpu->lock);

		/* this will destroy the states as well */
		drm_plane_cleanup(plane);

		dpu_hw_sspp_destroy(pdpu->pipe_hw);

		kfree(pdpu);
	}
}