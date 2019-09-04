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
struct vdec_vp9_vsi {int /*<<< orphan*/  frm_num; int /*<<< orphan*/  pic_h; int /*<<< orphan*/  pic_w; int /*<<< orphan*/  show_existing_frame; } ;
struct vdec_vp9_inst {int /*<<< orphan*/  vpu; struct vdec_vp9_vsi* vsi; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtk_vcodec_debug (struct vdec_vp9_inst*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  mtk_vcodec_err (struct vdec_vp9_inst*,char*,...) ; 
 int /*<<< orphan*/  vp9_swap_frm_bufs (struct vdec_vp9_inst*) ; 
 int vp9_wait_dec_end (struct vdec_vp9_inst*) ; 
 scalar_t__ vpu_dec_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool vp9_decode_end_proc(struct vdec_vp9_inst *inst)
{
	struct vdec_vp9_vsi *vsi = inst->vsi;
	bool ret = false;

	if (!vsi->show_existing_frame) {
		ret = vp9_wait_dec_end(inst);
		if (!ret) {
			mtk_vcodec_err(inst, "Decode failed, Decode Timeout @[%d]",
				vsi->frm_num);
			return false;
		}

		if (vpu_dec_end(&inst->vpu)) {
			mtk_vcodec_err(inst, "vp9_dec_vpu_end failed");
			return false;
		}
		mtk_vcodec_debug(inst, "Decode Ok @%d (%d/%d)", vsi->frm_num,
				vsi->pic_w, vsi->pic_h);
	} else {
		mtk_vcodec_debug(inst, "Decode Ok @%d (show_existing_frame)",
				vsi->frm_num);
	}

	vp9_swap_frm_bufs(inst);
	vsi->frm_num++;
	return true;
}