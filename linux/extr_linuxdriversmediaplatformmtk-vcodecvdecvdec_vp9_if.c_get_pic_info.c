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
struct vdec_pic_info {int /*<<< orphan*/  c_len_sz; int /*<<< orphan*/  c_bs_sz; int /*<<< orphan*/  y_len_sz; int /*<<< orphan*/  y_bs_sz; int /*<<< orphan*/  buf_h; int /*<<< orphan*/  buf_w; int /*<<< orphan*/  pic_h; int /*<<< orphan*/  pic_w; } ;
struct TYPE_2__ {int /*<<< orphan*/  buf_h; int /*<<< orphan*/  buf_w; int /*<<< orphan*/  pic_h; int /*<<< orphan*/  pic_w; int /*<<< orphan*/  buf_len_sz_c; int /*<<< orphan*/  buf_len_sz_y; int /*<<< orphan*/  buf_sz_c_bs; int /*<<< orphan*/  buf_sz_y_bs; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtk_vcodec_debug (struct vdec_vp9_inst*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_pic_info(struct vdec_vp9_inst *inst, struct vdec_pic_info *pic)
{
	pic->y_bs_sz = inst->vsi->buf_sz_y_bs;
	pic->c_bs_sz = inst->vsi->buf_sz_c_bs;
	pic->y_len_sz = inst->vsi->buf_len_sz_y;
	pic->c_len_sz = inst->vsi->buf_len_sz_c;

	pic->pic_w = inst->vsi->pic_w;
	pic->pic_h = inst->vsi->pic_h;
	pic->buf_w = inst->vsi->buf_w;
	pic->buf_h = inst->vsi->buf_h;

	mtk_vcodec_debug(inst, "pic(%d, %d), buf(%d, %d)",
		 pic->pic_w, pic->pic_h, pic->buf_w, pic->buf_h);
	mtk_vcodec_debug(inst, "Y(%d, %d), C(%d, %d)", pic->y_bs_sz,
		 pic->y_len_sz, pic->c_bs_sz, pic->c_len_sz);
}