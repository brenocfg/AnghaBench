#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int error; } ;
struct TYPE_7__ {int /*<<< orphan*/  index; struct vsp1_device* vsp1; } ;
struct TYPE_5__ {void* vflip; void* rotate; void* hflip; } ;
struct TYPE_6__ {TYPE_1__ ctrls; int /*<<< orphan*/  lock; } ;
struct vsp1_rwpf {TYPE_4__ ctrls; TYPE_3__ entity; TYPE_2__ flip; } ;
struct vsp1_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_CID_HFLIP ; 
 int /*<<< orphan*/  V4L2_CID_ROTATE ; 
 int /*<<< orphan*/  V4L2_CID_VFLIP ; 
 int /*<<< orphan*/  VSP1_HAS_WPF_HFLIP ; 
 int /*<<< orphan*/  VSP1_HAS_WPF_VFLIP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_cluster (int,void**) ; 
 void* v4l2_ctrl_new_std (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ vsp1_feature (struct vsp1_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsp1_rwpf_init_ctrls (struct vsp1_rwpf*,unsigned int) ; 
 int /*<<< orphan*/  vsp1_wpf_ctrl_ops ; 

__attribute__((used)) static int wpf_init_controls(struct vsp1_rwpf *wpf)
{
	struct vsp1_device *vsp1 = wpf->entity.vsp1;
	unsigned int num_flip_ctrls;

	spin_lock_init(&wpf->flip.lock);

	if (wpf->entity.index != 0) {
		/* Only WPF0 supports flipping. */
		num_flip_ctrls = 0;
	} else if (vsp1_feature(vsp1, VSP1_HAS_WPF_HFLIP)) {
		/*
		 * When horizontal flip is supported the WPF implements three
		 * controls (horizontal flip, vertical flip and rotation).
		 */
		num_flip_ctrls = 3;
	} else if (vsp1_feature(vsp1, VSP1_HAS_WPF_VFLIP)) {
		/*
		 * When only vertical flip is supported the WPF implements a
		 * single control (vertical flip).
		 */
		num_flip_ctrls = 1;
	} else {
		/* Otherwise flipping is not supported. */
		num_flip_ctrls = 0;
	}

	vsp1_rwpf_init_ctrls(wpf, num_flip_ctrls);

	if (num_flip_ctrls >= 1) {
		wpf->flip.ctrls.vflip =
			v4l2_ctrl_new_std(&wpf->ctrls, &vsp1_wpf_ctrl_ops,
					  V4L2_CID_VFLIP, 0, 1, 1, 0);
	}

	if (num_flip_ctrls == 3) {
		wpf->flip.ctrls.hflip =
			v4l2_ctrl_new_std(&wpf->ctrls, &vsp1_wpf_ctrl_ops,
					  V4L2_CID_HFLIP, 0, 1, 1, 0);
		wpf->flip.ctrls.rotate =
			v4l2_ctrl_new_std(&wpf->ctrls, &vsp1_wpf_ctrl_ops,
					  V4L2_CID_ROTATE, 0, 270, 90, 0);
		v4l2_ctrl_cluster(3, &wpf->flip.ctrls.vflip);
	}

	if (wpf->ctrls.error) {
		dev_err(vsp1->dev, "wpf%u: failed to initialize controls\n",
			wpf->entity.index);
		return wpf->ctrls.error;
	}

	return 0;
}