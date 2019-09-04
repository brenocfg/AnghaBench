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
struct vdec_vp9_inst {TYPE_1__* vsi; } ;
struct v4l2_rect {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ top; scalar_t__ left; } ;
struct TYPE_2__ {int /*<<< orphan*/  pic_h; int /*<<< orphan*/  pic_w; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtk_vcodec_debug (struct vdec_vp9_inst*,char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_crop_info(struct vdec_vp9_inst *inst, struct v4l2_rect *cr)
{
	cr->left = 0;
	cr->top = 0;
	cr->width = inst->vsi->pic_w;
	cr->height = inst->vsi->pic_h;
	mtk_vcodec_debug(inst, "get crop info l=%d, t=%d, w=%d, h=%d\n",
			 cr->left, cr->top, cr->width, cr->height);
}