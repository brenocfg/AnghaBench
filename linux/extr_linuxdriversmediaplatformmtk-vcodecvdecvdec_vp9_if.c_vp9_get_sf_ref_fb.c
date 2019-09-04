#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vdec_vp9_vsi {TYPE_2__* sf_ref_fb; scalar_t__ buf_len_sz_c; scalar_t__ buf_sz_c_bs; scalar_t__ buf_len_sz_y; scalar_t__ buf_sz_y_bs; } ;
struct vdec_vp9_inst {int /*<<< orphan*/  ctx; struct vdec_vp9_vsi* vsi; } ;
struct mtk_vcodec_mem {scalar_t__ size; int /*<<< orphan*/ * va; } ;
struct TYPE_3__ {struct mtk_vcodec_mem base_c; struct mtk_vcodec_mem base_y; } ;
struct TYPE_4__ {scalar_t__ used; TYPE_1__ fb; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  mtk_vcodec_err (struct vdec_vp9_inst*,char*) ; 
 scalar_t__ mtk_vcodec_mem_alloc (int /*<<< orphan*/ ,struct mtk_vcodec_mem*) ; 

__attribute__((used)) static int vp9_get_sf_ref_fb(struct vdec_vp9_inst *inst)
{
	int idx;
	struct mtk_vcodec_mem *mem_basy_y;
	struct mtk_vcodec_mem *mem_basy_c;
	struct vdec_vp9_vsi *vsi = inst->vsi;

	for (idx = 0;
		idx < ARRAY_SIZE(vsi->sf_ref_fb);
		idx++) {
		if (vsi->sf_ref_fb[idx].fb.base_y.va &&
		    vsi->sf_ref_fb[idx].used == 0) {
			return idx;
		}
	}

	for (idx = 0;
		idx < ARRAY_SIZE(vsi->sf_ref_fb);
		idx++) {
		if (vsi->sf_ref_fb[idx].fb.base_y.va == NULL)
			break;
	}

	if (idx == ARRAY_SIZE(vsi->sf_ref_fb)) {
		mtk_vcodec_err(inst, "List Full");
		return -1;
	}

	mem_basy_y = &vsi->sf_ref_fb[idx].fb.base_y;
	mem_basy_y->size = vsi->buf_sz_y_bs +
		vsi->buf_len_sz_y;

	if (mtk_vcodec_mem_alloc(inst->ctx, mem_basy_y)) {
		mtk_vcodec_err(inst, "Cannot allocate sf_ref_buf y_buf");
		return -1;
	}

	mem_basy_c = &vsi->sf_ref_fb[idx].fb.base_c;
	mem_basy_c->size = vsi->buf_sz_c_bs +
		vsi->buf_len_sz_c;

	if (mtk_vcodec_mem_alloc(inst->ctx, mem_basy_c)) {
		mtk_vcodec_err(inst, "Cannot allocate sf_ref_fb c_buf");
		return -1;
	}
	vsi->sf_ref_fb[idx].used = 0;

	return idx;
}