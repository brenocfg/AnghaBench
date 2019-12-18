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
struct TYPE_4__ {scalar_t__ state; unsigned int bs_size; int /*<<< orphan*/  is_key_frm; } ;
struct venc_h264_inst {TYPE_2__ vpu_inst; int /*<<< orphan*/  frm_cnt; TYPE_1__* work_bufs; } ;
struct venc_frm_buf {int dummy; } ;
struct mtk_vcodec_mem {int /*<<< orphan*/  va; } ;
struct TYPE_3__ {int /*<<< orphan*/  va; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  H264_BS_MODE_FRAME ; 
 unsigned int MTK_VENC_IRQ_STATUS_FRM ; 
 size_t VENC_H264_VPU_WORK_BUF_SKIP_FRAME ; 
 int /*<<< orphan*/  VENC_PIC_BITSTREAM_BYTE_CNT ; 
 scalar_t__ VEN_IPI_MSG_ENC_STATE_SKIP ; 
 unsigned int h264_enc_wait_venc_done (struct venc_h264_inst*) ; 
 unsigned int h264_read_reg (struct venc_h264_inst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mtk_vcodec_debug (struct venc_h264_inst*,char*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_vcodec_debug_enter (struct venc_h264_inst*) ; 
 int /*<<< orphan*/  mtk_vcodec_err (struct venc_h264_inst*,char*,unsigned int) ; 
 int vpu_enc_encode (TYPE_2__*,int /*<<< orphan*/ ,struct venc_frm_buf*,struct mtk_vcodec_mem*,unsigned int*) ; 

__attribute__((used)) static int h264_encode_frame(struct venc_h264_inst *inst,
			     struct venc_frm_buf *frm_buf,
			     struct mtk_vcodec_mem *bs_buf,
			     unsigned int *bs_size)
{
	int ret = 0;
	unsigned int irq_status;

	mtk_vcodec_debug_enter(inst);

	ret = vpu_enc_encode(&inst->vpu_inst, H264_BS_MODE_FRAME, frm_buf,
			     bs_buf, bs_size);
	if (ret)
		return ret;

	/*
	 * skip frame case: The skip frame buffer is composed by vpu side only,
	 * it does not trigger the hw, so skip the wait interrupt operation.
	 */
	if (inst->vpu_inst.state == VEN_IPI_MSG_ENC_STATE_SKIP) {
		*bs_size = inst->vpu_inst.bs_size;
		memcpy(bs_buf->va,
		       inst->work_bufs[VENC_H264_VPU_WORK_BUF_SKIP_FRAME].va,
		       *bs_size);
		++inst->frm_cnt;
		return ret;
	}

	irq_status = h264_enc_wait_venc_done(inst);
	if (irq_status != MTK_VENC_IRQ_STATUS_FRM) {
		mtk_vcodec_err(inst, "irq_status=%d failed", irq_status);
		return -EIO;
	}

	*bs_size = h264_read_reg(inst, VENC_PIC_BITSTREAM_BYTE_CNT);

	++inst->frm_cnt;
	mtk_vcodec_debug(inst, "frm %d bs_size %d key_frm %d <-",
			 inst->frm_cnt, *bs_size, inst->vpu_inst.is_key_frm);

	return ret;
}