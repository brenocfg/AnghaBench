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
struct vb2_v4l2_buffer {int dummy; } ;
struct vb2_buffer {int /*<<< orphan*/  vb2_queue; } ;
struct mcam_vb_buffer {int /*<<< orphan*/  queue; } ;
struct mcam_camera {scalar_t__ state; int /*<<< orphan*/  dev_lock; int /*<<< orphan*/  flags; int /*<<< orphan*/  buffers; } ;

/* Variables and functions */
 int /*<<< orphan*/  CF_SG_RESTART ; 
 scalar_t__ S_BUFWAIT ; 
 scalar_t__ S_STREAMING ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mcam_read_setup (struct mcam_camera*) ; 
 int /*<<< orphan*/  mcam_sg_restart (struct mcam_camera*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 struct mcam_camera* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 
 struct mcam_vb_buffer* vb_to_mvb (struct vb2_v4l2_buffer*) ; 

__attribute__((used)) static void mcam_vb_buf_queue(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct mcam_vb_buffer *mvb = vb_to_mvb(vbuf);
	struct mcam_camera *cam = vb2_get_drv_priv(vb->vb2_queue);
	unsigned long flags;
	int start;

	spin_lock_irqsave(&cam->dev_lock, flags);
	start = (cam->state == S_BUFWAIT) && !list_empty(&cam->buffers);
	list_add(&mvb->queue, &cam->buffers);
	if (cam->state == S_STREAMING && test_bit(CF_SG_RESTART, &cam->flags))
		mcam_sg_restart(cam);
	spin_unlock_irqrestore(&cam->dev_lock, flags);
	if (start)
		mcam_read_setup(cam);
}