#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct vdec_fb {int dummy; } ;
struct mtk_vcodec_mem {unsigned int size; scalar_t__ va; } ;
struct vdec_vp9_vsi {unsigned char* sf_bs_buf; unsigned int sf_frm_cnt; unsigned int sf_frm_idx; size_t sf_next_ref_fb_idx; size_t new_fb_idx; scalar_t__ frm_to_show_idx; scalar_t__ resolution_changed; TYPE_4__* frm_bufs; TYPE_5__* frm_refs; scalar_t__ show_existing_frame; int /*<<< orphan*/  frm_num; TYPE_2__* sf_ref_fb; int /*<<< orphan*/ * sf_frm_sz; scalar_t__* sf_frm_offset; int /*<<< orphan*/  sf_init; struct vdec_fb fb; struct mtk_vcodec_mem bs; } ;
struct TYPE_6__ {int /*<<< orphan*/  size; int /*<<< orphan*/  va; } ;
struct vdec_vp9_inst {int /*<<< orphan*/  total_frm_cnt; struct vdec_fb* cur_fb; int /*<<< orphan*/  vpu; TYPE_1__ seg_id_buf; struct vdec_vp9_vsi* vsi; } ;
struct TYPE_10__ {unsigned int idx; TYPE_3__* buf; } ;
struct TYPE_8__ {struct vdec_fb* fb; } ;
struct TYPE_9__ {TYPE_3__ buf; } ;
struct TYPE_7__ {struct vdec_fb fb; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_5__*) ; 
 int EINVAL ; 
 int EIO ; 
 scalar_t__ VP9_MAX_FRM_BUF_NUM ; 
 unsigned int VP9_SUPER_FRAME_BS_SZ ; 
 int /*<<< orphan*/  memcpy (void*,void*,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_vcodec_debug (struct vdec_vp9_inst*,char*,...) ; 
 int /*<<< orphan*/  mtk_vcodec_err (struct vdec_vp9_inst*,char*) ; 
 int validate_vsi_array_indexes (struct vdec_vp9_inst*,struct vdec_vp9_vsi*) ; 
 int /*<<< orphan*/  vp9_add_to_fb_free_list (struct vdec_vp9_inst*,struct vdec_fb*) ; 
 int /*<<< orphan*/  vp9_add_to_fb_use_list (struct vdec_vp9_inst*,struct vdec_fb*) ; 
 int /*<<< orphan*/  vp9_alloc_work_buf (struct vdec_vp9_inst*) ; 
 int vp9_decode_end_proc (struct vdec_vp9_inst*) ; 
 scalar_t__ vp9_is_last_sub_frm (struct vdec_vp9_inst*) ; 
 int /*<<< orphan*/  vp9_is_sf_ref_fb (struct vdec_vp9_inst*,struct vdec_fb*) ; 
 int /*<<< orphan*/  vp9_ref_cnt_fb (struct vdec_vp9_inst*,size_t*,scalar_t__) ; 
 int /*<<< orphan*/  vp9_reset (struct vdec_vp9_inst*) ; 
 int vpu_dec_start (int /*<<< orphan*/ *,unsigned int*,int) ; 

__attribute__((used)) static int vdec_vp9_decode(void *h_vdec, struct mtk_vcodec_mem *bs,
			   struct vdec_fb *fb, bool *res_chg)
{
	int ret = 0;
	struct vdec_vp9_inst *inst = (struct vdec_vp9_inst *)h_vdec;
	struct vdec_vp9_vsi *vsi = inst->vsi;
	u32 data[3];
	int i;

	*res_chg = false;

	if ((bs == NULL) && (fb == NULL)) {
		mtk_vcodec_debug(inst, "[EOS]");
		vp9_reset(inst);
		return ret;
	}

	if (bs == NULL) {
		mtk_vcodec_err(inst, "bs == NULL");
		return -EINVAL;
	}

	mtk_vcodec_debug(inst, "Input BS Size = %zu", bs->size);

	while (1) {
		struct vdec_fb *cur_fb = NULL;

		data[0] = *((unsigned int *)bs->va);
		data[1] = *((unsigned int *)(bs->va + 4));
		data[2] = *((unsigned int *)(bs->va + 8));

		vsi->bs = *bs;

		if (fb)
			vsi->fb = *fb;

		if (!vsi->sf_init) {
			unsigned int sf_bs_sz;
			unsigned int sf_bs_off;
			unsigned char *sf_bs_src;
			unsigned char *sf_bs_dst;

			sf_bs_sz = bs->size > VP9_SUPER_FRAME_BS_SZ ?
					VP9_SUPER_FRAME_BS_SZ : bs->size;
			sf_bs_off = VP9_SUPER_FRAME_BS_SZ - sf_bs_sz;
			sf_bs_src = bs->va + bs->size - sf_bs_sz;
			sf_bs_dst = vsi->sf_bs_buf + sf_bs_off;
			memcpy(sf_bs_dst, sf_bs_src, sf_bs_sz);
		} else {
			if ((vsi->sf_frm_cnt > 0) &&
				(vsi->sf_frm_idx < vsi->sf_frm_cnt)) {
				unsigned int idx = vsi->sf_frm_idx;

				memcpy((void *)bs->va,
					(void *)(bs->va +
					vsi->sf_frm_offset[idx]),
					vsi->sf_frm_sz[idx]);
			}
		}
		memset(inst->seg_id_buf.va, 0, inst->seg_id_buf.size);
		ret = vpu_dec_start(&inst->vpu, data, 3);
		if (ret) {
			mtk_vcodec_err(inst, "vpu_dec_start failed");
			goto DECODE_ERROR;
		}

		ret = validate_vsi_array_indexes(inst, vsi);
		if (ret) {
			mtk_vcodec_err(inst, "Invalid values from VPU.");
			goto DECODE_ERROR;
		}

		if (vsi->resolution_changed) {
			if (!vp9_alloc_work_buf(inst)) {
				ret = -EIO;
				goto DECODE_ERROR;
			}
		}

		if (vsi->sf_frm_cnt > 0) {
			cur_fb = &vsi->sf_ref_fb[vsi->sf_next_ref_fb_idx].fb;

			if (vsi->sf_frm_idx < vsi->sf_frm_cnt)
				inst->cur_fb = cur_fb;
			else
				inst->cur_fb = fb;
		} else {
			inst->cur_fb = fb;
		}

		vsi->frm_bufs[vsi->new_fb_idx].buf.fb = inst->cur_fb;
		if (!vp9_is_sf_ref_fb(inst, inst->cur_fb))
			vp9_add_to_fb_use_list(inst, inst->cur_fb);

		mtk_vcodec_debug(inst, "[#pic %d]", vsi->frm_num);

		if (vsi->show_existing_frame)
			mtk_vcodec_debug(inst,
				"drv->new_fb_idx=%d, drv->frm_to_show_idx=%d",
				vsi->new_fb_idx, vsi->frm_to_show_idx);

		if (vsi->show_existing_frame && (vsi->frm_to_show_idx <
					VP9_MAX_FRM_BUF_NUM)) {
			mtk_vcodec_debug(inst,
				"Skip Decode drv->new_fb_idx=%d, drv->frm_to_show_idx=%d",
				vsi->new_fb_idx, vsi->frm_to_show_idx);

			vp9_ref_cnt_fb(inst, &vsi->new_fb_idx,
					vsi->frm_to_show_idx);
		}

		/* VPU assign the buffer pointer in its address space,
		 * reassign here
		 */
		for (i = 0; i < ARRAY_SIZE(vsi->frm_refs); i++) {
			unsigned int idx = vsi->frm_refs[i].idx;

			vsi->frm_refs[i].buf = &vsi->frm_bufs[idx].buf;
		}

		if (vsi->resolution_changed) {
			*res_chg = true;
			mtk_vcodec_debug(inst, "VDEC_ST_RESOLUTION_CHANGED");

			ret = 0;
			goto DECODE_ERROR;
		}

		if (vp9_decode_end_proc(inst) != true) {
			mtk_vcodec_err(inst, "vp9_decode_end_proc");
			ret = -EINVAL;
			goto DECODE_ERROR;
		}

		if (vp9_is_last_sub_frm(inst))
			break;

	}
	inst->total_frm_cnt++;

DECODE_ERROR:
	if (ret < 0)
		vp9_add_to_fb_free_list(inst, fb);

	return ret;
}