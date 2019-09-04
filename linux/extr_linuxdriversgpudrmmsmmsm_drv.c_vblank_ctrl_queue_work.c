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
struct vblank_event {int crtc_id; int enable; int /*<<< orphan*/  node; } ;
struct msm_vblank_ctrl {int /*<<< orphan*/  work; int /*<<< orphan*/  lock; int /*<<< orphan*/  event_list; } ;
struct msm_drm_private {TYPE_1__* disp_thread; struct msm_vblank_ctrl vblank_ctrl; } ;
struct TYPE_2__ {int /*<<< orphan*/  worker; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kthread_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct vblank_event* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int vblank_ctrl_queue_work(struct msm_drm_private *priv,
					int crtc_id, bool enable)
{
	struct msm_vblank_ctrl *vbl_ctrl = &priv->vblank_ctrl;
	struct vblank_event *vbl_ev;
	unsigned long flags;

	vbl_ev = kzalloc(sizeof(*vbl_ev), GFP_ATOMIC);
	if (!vbl_ev)
		return -ENOMEM;

	vbl_ev->crtc_id = crtc_id;
	vbl_ev->enable = enable;

	spin_lock_irqsave(&vbl_ctrl->lock, flags);
	list_add_tail(&vbl_ev->node, &vbl_ctrl->event_list);
	spin_unlock_irqrestore(&vbl_ctrl->lock, flags);

	kthread_queue_work(&priv->disp_thread[crtc_id].worker,
			&vbl_ctrl->work);

	return 0;
}