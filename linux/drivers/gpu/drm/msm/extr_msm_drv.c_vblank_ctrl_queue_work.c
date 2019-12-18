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
struct msm_vblank_work {int crtc_id; int enable; int /*<<< orphan*/  work; struct msm_drm_private* priv; } ;
struct msm_drm_private {int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct msm_vblank_work* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vblank_ctrl_worker ; 

__attribute__((used)) static int vblank_ctrl_queue_work(struct msm_drm_private *priv,
					int crtc_id, bool enable)
{
	struct msm_vblank_work *vbl_work;

	vbl_work = kzalloc(sizeof(*vbl_work), GFP_ATOMIC);
	if (!vbl_work)
		return -ENOMEM;

	INIT_WORK(&vbl_work->work, vblank_ctrl_worker);

	vbl_work->crtc_id = crtc_id;
	vbl_work->enable = enable;
	vbl_work->priv = priv;

	queue_work(priv->wq, &vbl_work->work);

	return 0;
}