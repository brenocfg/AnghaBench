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
struct vsp1_pipeline {int dummy; } ;
struct vsp1_entity {int /*<<< orphan*/  subdev; } ;
struct vsp1_drm_pipeline {int force_brx_release; int /*<<< orphan*/  wait_queue; int /*<<< orphan*/  du_private; int /*<<< orphan*/  (* du_complete ) (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ;struct vsp1_entity* uif; } ;

/* Variables and functions */
 unsigned int VSP1_DL_FRAME_END_INTERNAL ; 
 unsigned int VSP1_DU_STATUS_COMPLETE ; 
 unsigned int VSP1_DU_STATUS_WRITEBACK ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_uif (int /*<<< orphan*/ *) ; 
 struct vsp1_drm_pipeline* to_vsp1_drm_pipeline (struct vsp1_pipeline*) ; 
 int /*<<< orphan*/  vsp1_uif_get_crc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vsp1_du_pipeline_frame_end(struct vsp1_pipeline *pipe,
				       unsigned int completion)
{
	struct vsp1_drm_pipeline *drm_pipe = to_vsp1_drm_pipeline(pipe);

	if (drm_pipe->du_complete) {
		struct vsp1_entity *uif = drm_pipe->uif;
		unsigned int status = completion
				    & (VSP1_DU_STATUS_COMPLETE |
				       VSP1_DU_STATUS_WRITEBACK);
		u32 crc;

		crc = uif ? vsp1_uif_get_crc(to_uif(&uif->subdev)) : 0;
		drm_pipe->du_complete(drm_pipe->du_private, status, crc);
	}

	if (completion & VSP1_DL_FRAME_END_INTERNAL) {
		drm_pipe->force_brx_release = false;
		wake_up(&drm_pipe->wait_queue);
	}
}