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
struct vb2_queue {scalar_t__ type; int /*<<< orphan*/  drv_priv; } ;
struct s5p_mfc_dev {struct device** mem_dev; } ;
struct s5p_mfc_ctx {scalar_t__ state; unsigned int enc_dst_buf_size; unsigned int luma_size; unsigned int chroma_size; struct s5p_mfc_dev* dev; TYPE_2__* src_fmt; TYPE_1__* dst_fmt; } ;
struct device {int dummy; } ;
struct TYPE_4__ {unsigned int num_planes; } ;
struct TYPE_3__ {unsigned int num_planes; } ;

/* Variables and functions */
 size_t BANK_L_CTX ; 
 size_t BANK_R_CTX ; 
 int EINVAL ; 
 scalar_t__ IS_MFCV6_PLUS (struct s5p_mfc_dev*) ; 
 scalar_t__ MFCINST_GOT_INST ; 
 unsigned int MFC_ENC_CAP_PLANE_COUNT ; 
 unsigned int MFC_ENC_OUT_PLANE_COUNT ; 
 unsigned int MFC_MAX_BUFFERS ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 struct s5p_mfc_ctx* fh_to_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfc_err (char*,scalar_t__) ; 

__attribute__((used)) static int s5p_mfc_queue_setup(struct vb2_queue *vq,
			unsigned int *buf_count, unsigned int *plane_count,
			unsigned int psize[], struct device *alloc_devs[])
{
	struct s5p_mfc_ctx *ctx = fh_to_ctx(vq->drv_priv);
	struct s5p_mfc_dev *dev = ctx->dev;

	if (vq->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) {
		if (ctx->state != MFCINST_GOT_INST) {
			mfc_err("invalid state: %d\n", ctx->state);
			return -EINVAL;
		}

		if (ctx->dst_fmt)
			*plane_count = ctx->dst_fmt->num_planes;
		else
			*plane_count = MFC_ENC_CAP_PLANE_COUNT;
		if (*buf_count < 1)
			*buf_count = 1;
		if (*buf_count > MFC_MAX_BUFFERS)
			*buf_count = MFC_MAX_BUFFERS;
		psize[0] = ctx->enc_dst_buf_size;
		alloc_devs[0] = ctx->dev->mem_dev[BANK_L_CTX];
	} else if (vq->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
		if (ctx->src_fmt)
			*plane_count = ctx->src_fmt->num_planes;
		else
			*plane_count = MFC_ENC_OUT_PLANE_COUNT;

		if (*buf_count < 1)
			*buf_count = 1;
		if (*buf_count > MFC_MAX_BUFFERS)
			*buf_count = MFC_MAX_BUFFERS;

		psize[0] = ctx->luma_size;
		psize[1] = ctx->chroma_size;

		if (IS_MFCV6_PLUS(dev)) {
			alloc_devs[0] = ctx->dev->mem_dev[BANK_L_CTX];
			alloc_devs[1] = ctx->dev->mem_dev[BANK_L_CTX];
		} else {
			alloc_devs[0] = ctx->dev->mem_dev[BANK_R_CTX];
			alloc_devs[1] = ctx->dev->mem_dev[BANK_R_CTX];
		}
	} else {
		mfc_err("invalid queue type: %d\n", vq->type);
		return -EINVAL;
	}
	return 0;
}