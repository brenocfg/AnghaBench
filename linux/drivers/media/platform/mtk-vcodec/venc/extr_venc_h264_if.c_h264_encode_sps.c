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
struct venc_h264_inst {int /*<<< orphan*/  vpu_inst; } ;
struct mtk_vcodec_mem {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  H264_BS_MODE_SPS ; 
 unsigned int MTK_VENC_IRQ_STATUS_SPS ; 
 int /*<<< orphan*/  VENC_PIC_BITSTREAM_BYTE_CNT ; 
 unsigned int h264_enc_wait_venc_done (struct venc_h264_inst*) ; 
 unsigned int h264_read_reg (struct venc_h264_inst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_vcodec_debug (struct venc_h264_inst*,char*,unsigned int) ; 
 int /*<<< orphan*/  mtk_vcodec_debug_enter (struct venc_h264_inst*) ; 
 int /*<<< orphan*/  mtk_vcodec_err (struct venc_h264_inst*,char*,unsigned int) ; 
 int vpu_enc_encode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mtk_vcodec_mem*,unsigned int*) ; 

__attribute__((used)) static int h264_encode_sps(struct venc_h264_inst *inst,
			   struct mtk_vcodec_mem *bs_buf,
			   unsigned int *bs_size)
{
	int ret = 0;
	unsigned int irq_status;

	mtk_vcodec_debug_enter(inst);

	ret = vpu_enc_encode(&inst->vpu_inst, H264_BS_MODE_SPS, NULL,
			     bs_buf, bs_size);
	if (ret)
		return ret;

	irq_status = h264_enc_wait_venc_done(inst);
	if (irq_status != MTK_VENC_IRQ_STATUS_SPS) {
		mtk_vcodec_err(inst, "expect irq status %d",
			       MTK_VENC_IRQ_STATUS_SPS);
		return -EINVAL;
	}

	*bs_size = h264_read_reg(inst, VENC_PIC_BITSTREAM_BYTE_CNT);
	mtk_vcodec_debug(inst, "bs size %d <-", *bs_size);

	return ret;
}