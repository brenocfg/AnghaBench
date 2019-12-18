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
struct mtk_vcodec_mem {scalar_t__ va; } ;
struct vdec_vp9_inst {int /*<<< orphan*/  ctx; struct mtk_vcodec_mem seg_id_buf; struct mtk_vcodec_mem mv_buf; int /*<<< orphan*/  vpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtk_vcodec_err (struct vdec_vp9_inst*,char*) ; 
 int /*<<< orphan*/  mtk_vcodec_mem_free (int /*<<< orphan*/ ,struct mtk_vcodec_mem*) ; 
 int /*<<< orphan*/  vp9_free_all_sf_ref_fb (struct vdec_vp9_inst*) ; 
 int /*<<< orphan*/  vp9_free_inst (struct vdec_vp9_inst*) ; 
 int vpu_dec_deinit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vdec_vp9_deinit(void *h_vdec)
{
	struct vdec_vp9_inst *inst = (struct vdec_vp9_inst *)h_vdec;
	struct mtk_vcodec_mem *mem;
	int ret = 0;

	ret = vpu_dec_deinit(&inst->vpu);
	if (ret)
		mtk_vcodec_err(inst, "vpu_dec_deinit failed");

	mem = &inst->mv_buf;
	if (mem->va)
		mtk_vcodec_mem_free(inst->ctx, mem);

	mem = &inst->seg_id_buf;
	if (mem->va)
		mtk_vcodec_mem_free(inst->ctx, mem);

	vp9_free_all_sf_ref_fb(inst);
	vp9_free_inst(inst);
}