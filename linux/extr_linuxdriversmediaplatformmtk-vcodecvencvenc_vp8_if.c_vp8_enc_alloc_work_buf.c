#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct venc_vp8_vpu_buf {scalar_t__ size; int /*<<< orphan*/  iova; int /*<<< orphan*/  vpua; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct venc_vp8_inst {TYPE_3__* work_bufs; TYPE_2__ vpu_inst; int /*<<< orphan*/  ctx; TYPE_1__* vsi; } ;
struct TYPE_6__ {scalar_t__ size; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  va; } ;
struct TYPE_4__ {struct venc_vp8_vpu_buf* work_bufs; } ;

/* Variables and functions */
 int VENC_VP8_VPU_WORK_BUF_MAX ; 
 int VENC_VP8_VPU_WORK_BUF_RC_CODE ; 
 int VENC_VP8_VPU_WORK_BUF_RC_CODE2 ; 
 int VENC_VP8_VPU_WORK_BUF_RC_CODE3 ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,scalar_t__) ; 
 int /*<<< orphan*/  mtk_vcodec_debug (struct venc_vp8_inst*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mtk_vcodec_debug_enter (struct venc_vp8_inst*) ; 
 int /*<<< orphan*/  mtk_vcodec_debug_leave (struct venc_vp8_inst*) ; 
 int /*<<< orphan*/  mtk_vcodec_err (struct venc_vp8_inst*,char*,int) ; 
 int mtk_vcodec_mem_alloc (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  vp8_enc_free_work_buf (struct venc_vp8_inst*) ; 
 void* vpu_mapping_dm_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vp8_enc_alloc_work_buf(struct venc_vp8_inst *inst)
{
	int i;
	int ret = 0;
	struct venc_vp8_vpu_buf *wb = inst->vsi->work_bufs;

	mtk_vcodec_debug_enter(inst);

	for (i = 0; i < VENC_VP8_VPU_WORK_BUF_MAX; i++) {
		if (wb[i].size == 0)
			continue;
		/*
		 * This 'wb' structure is set by VPU side and shared to AP for
		 * buffer allocation and IO virtual addr mapping. For most of
		 * the buffers, AP will allocate the buffer according to 'size'
		 * field and store the IO virtual addr in 'iova' field. For the
		 * RC_CODEx buffers, they are pre-allocated in the VPU side
		 * because they are inside VPU SRAM, and save the VPU addr in
		 * the 'vpua' field. The AP will translate the VPU addr to the
		 * corresponding IO virtual addr and store in 'iova' field.
		 */
		inst->work_bufs[i].size = wb[i].size;
		ret = mtk_vcodec_mem_alloc(inst->ctx, &inst->work_bufs[i]);
		if (ret) {
			mtk_vcodec_err(inst,
				       "cannot alloc work_bufs[%d]", i);
			goto err_alloc;
		}
		/*
		 * This RC_CODEx is pre-allocated by VPU and saved in VPU addr.
		 * So we need use memcpy to copy RC_CODEx from VPU addr into IO
		 * virtual addr in 'iova' field for reg setting in VPU side.
		 */
		if (i == VENC_VP8_VPU_WORK_BUF_RC_CODE ||
		    i == VENC_VP8_VPU_WORK_BUF_RC_CODE2 ||
		    i == VENC_VP8_VPU_WORK_BUF_RC_CODE3) {
			void *tmp_va;

			tmp_va = vpu_mapping_dm_addr(inst->vpu_inst.dev,
						     wb[i].vpua);
			memcpy(inst->work_bufs[i].va, tmp_va, wb[i].size);
		}
		wb[i].iova = inst->work_bufs[i].dma_addr;

		mtk_vcodec_debug(inst,
				 "work_bufs[%d] va=0x%p,iova=%pad,size=%zu",
				 i, inst->work_bufs[i].va,
				 &inst->work_bufs[i].dma_addr,
				 inst->work_bufs[i].size);
	}

	mtk_vcodec_debug_leave(inst);

	return ret;

err_alloc:
	vp8_enc_free_work_buf(inst);

	return ret;
}