#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int error; } ;
struct TYPE_5__ {TYPE_3__* ctrl_handler; } ;
struct TYPE_6__ {TYPE_1__ subdev; } ;
struct vsp1_rwpf {TYPE_3__ ctrls; TYPE_2__ entity; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_CID_ALPHA_COMPONENT ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_3__*,unsigned int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  vsp1_rwpf_ctrl_ops ; 

int vsp1_rwpf_init_ctrls(struct vsp1_rwpf *rwpf, unsigned int ncontrols)
{
	v4l2_ctrl_handler_init(&rwpf->ctrls, ncontrols + 1);
	v4l2_ctrl_new_std(&rwpf->ctrls, &vsp1_rwpf_ctrl_ops,
			  V4L2_CID_ALPHA_COMPONENT, 0, 255, 1, 255);

	rwpf->entity.subdev.ctrl_handler = &rwpf->ctrls;

	return rwpf->ctrls.error;
}