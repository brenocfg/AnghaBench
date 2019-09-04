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
struct venc_h264_vpu_buf {int size; scalar_t__ iova; int /*<<< orphan*/  vpua; } ;
struct TYPE_6__ {int size; scalar_t__ dma_addr; void* va; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct venc_h264_inst {TYPE_3__ pps_buf; int /*<<< orphan*/  ctx; TYPE_3__* work_bufs; TYPE_2__ vpu_inst; TYPE_1__* vsi; } ;
struct TYPE_4__ {struct venc_h264_vpu_buf* work_bufs; } ;

/* Variables and functions */
 int VENC_H264_VPU_WORK_BUF_MAX ; 
 int VENC_H264_VPU_WORK_BUF_RC_CODE ; 
 int VENC_H264_VPU_WORK_BUF_SKIP_FRAME ; 
 int /*<<< orphan*/  h264_enc_free_work_buf (struct venc_h264_inst*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  mtk_vcodec_debug (struct venc_h264_inst*,char*,int,void*,scalar_t__*,int) ; 
 int /*<<< orphan*/  mtk_vcodec_debug_enter (struct venc_h264_inst*) ; 
 int /*<<< orphan*/  mtk_vcodec_debug_leave (struct venc_h264_inst*) ; 
 int /*<<< orphan*/  mtk_vcodec_err (struct venc_h264_inst*,char*,...) ; 
 int mtk_vcodec_mem_alloc (int /*<<< orphan*/ ,TYPE_3__*) ; 
 void* vpu_mapping_dm_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int h264_enc_alloc_work_buf(struct venc_h264_inst *inst)
{
	int i;
	int ret = 0;
	struct venc_h264_vpu_buf *wb = inst->vsi->work_bufs;

	mtk_vcodec_debug_enter(inst);

	for (i = 0; i < VENC_H264_VPU_WORK_BUF_MAX; i++) {
		/*
		 * This 'wb' structure is set by VPU side and shared to AP for
		 * buffer allocation and IO virtual addr mapping. For most of
		 * the buffers, AP will allocate the buffer according to 'size'
		 * field and store the IO virtual addr in 'iova' field. There
		 * are two exceptions:
		 * (1) RC_CODE buffer, it's pre-allocated in the VPU side, and
		 * save the VPU addr in the 'vpua' field. The AP will translate
		 * the VPU addr to the corresponding IO virtual addr and store
		 * in 'iova' field for reg setting in VPU side.
		 * (2) SKIP_FRAME buffer, it's pre-allocated in the VPU side,
		 * and save the VPU addr in the 'vpua' field. The AP will
		 * translate the VPU addr to the corresponding AP side virtual
		 * address and do some memcpy access to move to bitstream buffer
		 * assigned by v4l2 layer.
		 */
		inst->work_bufs[i].size = wb[i].size;
		if (i == VENC_H264_VPU_WORK_BUF_SKIP_FRAME) {
			inst->work_bufs[i].va = vpu_mapping_dm_addr(
				inst->vpu_inst.dev, wb[i].vpua);
			inst->work_bufs[i].dma_addr = 0;
		} else {
			ret = mtk_vcodec_mem_alloc(inst->ctx,
						   &inst->work_bufs[i]);
			if (ret) {
				mtk_vcodec_err(inst,
					       "cannot allocate buf %d", i);
				goto err_alloc;
			}
			/*
			 * This RC_CODE is pre-allocated by VPU and saved in VPU
			 * addr. So we need use memcpy to copy RC_CODE from VPU
			 * addr into IO virtual addr in 'iova' field for reg
			 * setting in VPU side.
			 */
			if (i == VENC_H264_VPU_WORK_BUF_RC_CODE) {
				void *tmp_va;

				tmp_va = vpu_mapping_dm_addr(inst->vpu_inst.dev,
							     wb[i].vpua);
				memcpy(inst->work_bufs[i].va, tmp_va,
				       wb[i].size);
			}
		}
		wb[i].iova = inst->work_bufs[i].dma_addr;

		mtk_vcodec_debug(inst,
				 "work_buf[%d] va=0x%p iova=%pad size=%zu",
				 i, inst->work_bufs[i].va,
				 &inst->work_bufs[i].dma_addr,
				 inst->work_bufs[i].size);
	}

	/* the pps_buf is used by AP side only */
	inst->pps_buf.size = 128;
	ret = mtk_vcodec_mem_alloc(inst->ctx, &inst->pps_buf);
	if (ret) {
		mtk_vcodec_err(inst, "cannot allocate pps_buf");
		goto err_alloc;
	}

	mtk_vcodec_debug_leave(inst);

	return ret;

err_alloc:
	h264_enc_free_work_buf(inst);

	return ret;
}