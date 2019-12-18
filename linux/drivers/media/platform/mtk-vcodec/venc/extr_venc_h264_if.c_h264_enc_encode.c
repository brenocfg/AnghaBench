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
struct TYPE_3__ {int is_key_frm; } ;
struct venc_h264_inst {TYPE_1__ vpu_inst; int /*<<< orphan*/  prepend_hdr; struct mtk_vcodec_ctx* ctx; } ;
struct venc_frm_buf {int dummy; } ;
struct venc_done_result {unsigned int bs_size; int is_key_frm; } ;
struct mtk_vcodec_mem {int /*<<< orphan*/  size; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  va; } ;
struct mtk_vcodec_ctx {TYPE_2__* dev; } ;
typedef  enum venc_start_opt { ____Placeholder_venc_start_opt } venc_start_opt ;
struct TYPE_4__ {int /*<<< orphan*/  enc_irq; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  H264_FILLER_MARKER_SIZE ; 
#define  VENC_START_OPT_ENCODE_FRAME 129 
#define  VENC_START_OPT_ENCODE_SEQUENCE_HEADER 128 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h264_encode_filler (struct venc_h264_inst*,int /*<<< orphan*/ ,int) ; 
 int h264_encode_frame (struct venc_h264_inst*,struct venc_frm_buf*,struct mtk_vcodec_mem*,unsigned int*) ; 
 int h264_encode_header (struct venc_h264_inst*,struct mtk_vcodec_mem*,unsigned int*) ; 
 int /*<<< orphan*/  mtk_vcodec_debug (struct venc_h264_inst*,char*,...) ; 
 int /*<<< orphan*/  mtk_vcodec_err (struct venc_h264_inst*,char*,int) ; 

__attribute__((used)) static int h264_enc_encode(void *handle,
			   enum venc_start_opt opt,
			   struct venc_frm_buf *frm_buf,
			   struct mtk_vcodec_mem *bs_buf,
			   struct venc_done_result *result)
{
	int ret = 0;
	struct venc_h264_inst *inst = (struct venc_h264_inst *)handle;
	struct mtk_vcodec_ctx *ctx = inst->ctx;

	mtk_vcodec_debug(inst, "opt %d ->", opt);

	enable_irq(ctx->dev->enc_irq);

	switch (opt) {
	case VENC_START_OPT_ENCODE_SEQUENCE_HEADER: {
		unsigned int bs_size_hdr;

		ret = h264_encode_header(inst, bs_buf, &bs_size_hdr);
		if (ret)
			goto encode_err;

		result->bs_size = bs_size_hdr;
		result->is_key_frm = false;
		break;
	}

	case VENC_START_OPT_ENCODE_FRAME: {
		int hdr_sz;
		int hdr_sz_ext;
		int filler_sz = 0;
		const int bs_alignment = 128;
		struct mtk_vcodec_mem tmp_bs_buf;
		unsigned int bs_size_hdr;
		unsigned int bs_size_frm;

		if (!inst->prepend_hdr) {
			ret = h264_encode_frame(inst, frm_buf, bs_buf,
						&result->bs_size);
			if (ret)
				goto encode_err;
			result->is_key_frm = inst->vpu_inst.is_key_frm;
			break;
		}

		mtk_vcodec_debug(inst, "h264_encode_frame prepend SPS/PPS");

		ret = h264_encode_header(inst, bs_buf, &bs_size_hdr);
		if (ret)
			goto encode_err;

		hdr_sz = bs_size_hdr;
		hdr_sz_ext = (hdr_sz & (bs_alignment - 1));
		if (hdr_sz_ext) {
			filler_sz = bs_alignment - hdr_sz_ext;
			if (hdr_sz_ext + H264_FILLER_MARKER_SIZE > bs_alignment)
				filler_sz += bs_alignment;
			h264_encode_filler(inst, bs_buf->va + hdr_sz,
					   filler_sz);
		}

		tmp_bs_buf.va = bs_buf->va + hdr_sz + filler_sz;
		tmp_bs_buf.dma_addr = bs_buf->dma_addr + hdr_sz + filler_sz;
		tmp_bs_buf.size = bs_buf->size - (hdr_sz + filler_sz);

		ret = h264_encode_frame(inst, frm_buf, &tmp_bs_buf,
					&bs_size_frm);
		if (ret)
			goto encode_err;

		result->bs_size = hdr_sz + filler_sz + bs_size_frm;

		mtk_vcodec_debug(inst, "hdr %d filler %d frame %d bs %d",
				 hdr_sz, filler_sz, bs_size_frm,
				 result->bs_size);

		inst->prepend_hdr = 0;
		result->is_key_frm = inst->vpu_inst.is_key_frm;
		break;
	}

	default:
		mtk_vcodec_err(inst, "venc_start_opt %d not supported", opt);
		ret = -EINVAL;
		break;
	}

encode_err:

	disable_irq(ctx->dev->enc_irq);
	mtk_vcodec_debug(inst, "opt %d <-", opt);

	return ret;
}