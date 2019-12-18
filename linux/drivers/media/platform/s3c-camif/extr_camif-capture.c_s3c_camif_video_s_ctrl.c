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
struct v4l2_ctrl {int id; int /*<<< orphan*/  val; int /*<<< orphan*/  name; struct camif_vp* priv; } ;
struct camif_vp {int /*<<< orphan*/  state; int /*<<< orphan*/  vflip; int /*<<< orphan*/  hflip; int /*<<< orphan*/  id; struct camif_dev* camif; } ;
struct camif_dev {int /*<<< orphan*/  slock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST_VP_CONFIG ; 
#define  V4L2_CID_HFLIP 129 
#define  V4L2_CID_VFLIP 128 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int s3c_camif_video_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct camif_vp *vp = ctrl->priv;
	struct camif_dev *camif = vp->camif;
	unsigned long flags;

	pr_debug("[vp%d] ctrl: %s, value: %d\n", vp->id,
		 ctrl->name, ctrl->val);

	spin_lock_irqsave(&camif->slock, flags);

	switch (ctrl->id) {
	case V4L2_CID_HFLIP:
		vp->hflip = ctrl->val;
		break;

	case V4L2_CID_VFLIP:
		vp->vflip = ctrl->val;
		break;
	}

	vp->state |= ST_VP_CONFIG;
	spin_unlock_irqrestore(&camif->slock, flags);
	return 0;
}