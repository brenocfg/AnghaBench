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
struct TYPE_2__ {int /*<<< orphan*/  is_key_frm; } ;
struct venc_vp8_inst {TYPE_1__ vpu_inst; int /*<<< orphan*/  frm_cnt; } ;
struct venc_frm_buf {int dummy; } ;
struct mtk_vcodec_mem {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 unsigned int MTK_VENC_IRQ_STATUS_FRM ; 
 int /*<<< orphan*/  mtk_vcodec_debug (struct venc_vp8_inst*,char*,unsigned int,...) ; 
 int /*<<< orphan*/  mtk_vcodec_err (struct venc_vp8_inst*,char*,...) ; 
 scalar_t__ vp8_enc_compose_one_frame (struct venc_vp8_inst*,struct mtk_vcodec_mem*,unsigned int*) ; 
 unsigned int vp8_enc_wait_venc_done (struct venc_vp8_inst*) ; 
 int vpu_enc_encode (TYPE_1__*,int /*<<< orphan*/ ,struct venc_frm_buf*,struct mtk_vcodec_mem*,unsigned int*) ; 

__attribute__((used)) static int vp8_enc_encode_frame(struct venc_vp8_inst *inst,
				struct venc_frm_buf *frm_buf,
				struct mtk_vcodec_mem *bs_buf,
				unsigned int *bs_size)
{
	int ret = 0;
	unsigned int irq_status;

	mtk_vcodec_debug(inst, "->frm_cnt=%d", inst->frm_cnt);

	ret = vpu_enc_encode(&inst->vpu_inst, 0, frm_buf, bs_buf, bs_size);
	if (ret)
		return ret;

	irq_status = vp8_enc_wait_venc_done(inst);
	if (irq_status != MTK_VENC_IRQ_STATUS_FRM) {
		mtk_vcodec_err(inst, "irq_status=%d failed", irq_status);
		return -EIO;
	}

	if (vp8_enc_compose_one_frame(inst, bs_buf, bs_size)) {
		mtk_vcodec_err(inst, "vp8_enc_compose_one_frame failed");
		return -EINVAL;
	}

	inst->frm_cnt++;
	mtk_vcodec_debug(inst, "<-size=%d key_frm=%d", *bs_size,
			 inst->vpu_inst.is_key_frm);

	return ret;
}