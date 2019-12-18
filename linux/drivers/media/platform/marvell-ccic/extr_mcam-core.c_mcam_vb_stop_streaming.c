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
struct vb2_queue {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  delivered; int /*<<< orphan*/  singles; int /*<<< orphan*/  frames; } ;
struct mcam_camera {scalar_t__ state; TYPE_1__ frame_state; } ;

/* Variables and functions */
 scalar_t__ S_BUFWAIT ; 
 scalar_t__ S_IDLE ; 
 scalar_t__ S_STREAMING ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  cam_dbg (struct mcam_camera*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcam_ctlr_stop_dma (struct mcam_camera*) ; 
 int /*<<< orphan*/  mcam_vb_requeue_bufs (struct vb2_queue*,int /*<<< orphan*/ ) ; 
 struct mcam_camera* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static void mcam_vb_stop_streaming(struct vb2_queue *vq)
{
	struct mcam_camera *cam = vb2_get_drv_priv(vq);

	cam_dbg(cam, "stop_streaming: %d frames, %d singles, %d delivered\n",
			cam->frame_state.frames, cam->frame_state.singles,
			cam->frame_state.delivered);
	if (cam->state == S_BUFWAIT) {
		/* They never gave us buffers */
		cam->state = S_IDLE;
		return;
	}
	if (cam->state != S_STREAMING)
		return;
	mcam_ctlr_stop_dma(cam);
	/*
	 * VB2 reclaims the buffers, so we need to forget
	 * about them.
	 */
	mcam_vb_requeue_bufs(vq, VB2_BUF_STATE_ERROR);
}