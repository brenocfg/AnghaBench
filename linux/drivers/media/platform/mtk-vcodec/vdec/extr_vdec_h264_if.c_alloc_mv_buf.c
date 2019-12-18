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
struct vdec_pic_info {int /*<<< orphan*/  buf_h; int /*<<< orphan*/  buf_w; } ;
struct vdec_h264_inst {TYPE_1__* vsi; int /*<<< orphan*/  ctx; struct mtk_vcodec_mem* mv_buf; } ;
struct mtk_vcodec_mem {unsigned int size; int /*<<< orphan*/  dma_addr; scalar_t__ va; } ;
struct TYPE_2__ {int /*<<< orphan*/ * mv_buf_dma; } ;

/* Variables and functions */
 int H264_MAX_FB_NUM ; 
 unsigned int get_mv_buf_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_vcodec_err (struct vdec_h264_inst*,char*) ; 
 int mtk_vcodec_mem_alloc (int /*<<< orphan*/ ,struct mtk_vcodec_mem*) ; 
 int /*<<< orphan*/  mtk_vcodec_mem_free (int /*<<< orphan*/ ,struct mtk_vcodec_mem*) ; 

__attribute__((used)) static int alloc_mv_buf(struct vdec_h264_inst *inst, struct vdec_pic_info *pic)
{
	int i;
	int err;
	struct mtk_vcodec_mem *mem = NULL;
	unsigned int buf_sz = get_mv_buf_size(pic->buf_w, pic->buf_h);

	for (i = 0; i < H264_MAX_FB_NUM; i++) {
		mem = &inst->mv_buf[i];
		if (mem->va)
			mtk_vcodec_mem_free(inst->ctx, mem);
		mem->size = buf_sz;
		err = mtk_vcodec_mem_alloc(inst->ctx, mem);
		if (err) {
			mtk_vcodec_err(inst, "failed to allocate mv buf");
			return err;
		}
		inst->vsi->mv_buf_dma[i] = mem->dma_addr;
	}

	return 0;
}