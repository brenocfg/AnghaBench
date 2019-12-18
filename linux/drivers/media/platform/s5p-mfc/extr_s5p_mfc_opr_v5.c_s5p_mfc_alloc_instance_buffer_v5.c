#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct s5p_mfc_dev {int* dma_base; TYPE_2__* variant; } ;
struct TYPE_7__ {int ofs; int dma; int /*<<< orphan*/  virt; int /*<<< orphan*/  size; } ;
struct s5p_mfc_ctx {scalar_t__ codec_mode; TYPE_3__ shm; TYPE_3__ ctx; struct s5p_mfc_dev* dev; } ;
struct s5p_mfc_buf_size_v5 {int /*<<< orphan*/  shm; int /*<<< orphan*/  non_h264_ctx; int /*<<< orphan*/  h264_ctx; } ;
struct TYPE_6__ {TYPE_1__* buf_size; } ;
struct TYPE_5__ {struct s5p_mfc_buf_size_v5* priv; } ;

/* Variables and functions */
 size_t BANK_L_CTX ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int MFC_BANK1_ALIGN_ORDER ; 
 int OFFSETA (int) ; 
 scalar_t__ S5P_MFC_CODEC_H264_DEC ; 
 scalar_t__ S5P_MFC_CODEC_H264_ENC ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfc_err (char*) ; 
 int s5p_mfc_alloc_priv_buf (struct s5p_mfc_dev*,size_t,TYPE_3__*) ; 
 int /*<<< orphan*/  s5p_mfc_release_priv_buf (struct s5p_mfc_dev*,TYPE_3__*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int s5p_mfc_alloc_instance_buffer_v5(struct s5p_mfc_ctx *ctx)
{
	struct s5p_mfc_dev *dev = ctx->dev;
	struct s5p_mfc_buf_size_v5 *buf_size = dev->variant->buf_size->priv;
	int ret;

	if (ctx->codec_mode == S5P_MFC_CODEC_H264_DEC ||
		ctx->codec_mode == S5P_MFC_CODEC_H264_ENC)
		ctx->ctx.size = buf_size->h264_ctx;
	else
		ctx->ctx.size = buf_size->non_h264_ctx;

	ret = s5p_mfc_alloc_priv_buf(dev, BANK_L_CTX, &ctx->ctx);
	if (ret) {
		mfc_err("Failed to allocate instance buffer\n");
		return ret;
	}
	ctx->ctx.ofs = OFFSETA(ctx->ctx.dma);

	/* Zero content of the allocated memory */
	memset(ctx->ctx.virt, 0, ctx->ctx.size);
	wmb();

	/* Initialize shared memory */
	ctx->shm.size = buf_size->shm;
	ret = s5p_mfc_alloc_priv_buf(dev, BANK_L_CTX, &ctx->shm);
	if (ret) {
		mfc_err("Failed to allocate shared memory buffer\n");
		s5p_mfc_release_priv_buf(dev, &ctx->ctx);
		return ret;
	}

	/* shared memory offset only keeps the offset from base (port a) */
	ctx->shm.ofs = ctx->shm.dma - dev->dma_base[BANK_L_CTX];
	BUG_ON(ctx->shm.ofs & ((1 << MFC_BANK1_ALIGN_ORDER) - 1));

	memset(ctx->shm.virt, 0, buf_size->shm);
	wmb();
	return 0;
}