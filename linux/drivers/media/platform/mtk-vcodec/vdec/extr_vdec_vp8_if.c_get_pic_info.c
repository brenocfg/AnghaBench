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
struct vdec_vp8_inst {TYPE_1__* vsi; } ;
struct vdec_pic_info {int /*<<< orphan*/ * fb_sz; int /*<<< orphan*/  buf_h; int /*<<< orphan*/  buf_w; int /*<<< orphan*/  pic_h; int /*<<< orphan*/  pic_w; } ;
struct TYPE_2__ {struct vdec_pic_info pic; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtk_vcodec_debug (struct vdec_vp8_inst*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void get_pic_info(struct vdec_vp8_inst *inst, struct vdec_pic_info *pic)
{
	*pic = inst->vsi->pic;

	mtk_vcodec_debug(inst, "pic(%d, %d), buf(%d, %d)",
			 pic->pic_w, pic->pic_h, pic->buf_w, pic->buf_h);
	mtk_vcodec_debug(inst, "fb size: Y(%d), C(%d)",
			 pic->fb_sz[0], pic->fb_sz[1]);
}