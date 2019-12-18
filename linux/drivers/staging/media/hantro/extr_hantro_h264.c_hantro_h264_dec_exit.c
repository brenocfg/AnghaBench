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
struct hantro_aux_buf {int /*<<< orphan*/  dma; int /*<<< orphan*/  cpu; int /*<<< orphan*/  size; } ;
struct hantro_h264_dec_hw_ctx {struct hantro_aux_buf priv; } ;
struct hantro_dev {int /*<<< orphan*/  dev; } ;
struct hantro_ctx {struct hantro_h264_dec_hw_ctx h264_dec; struct hantro_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hantro_h264_dec_exit(struct hantro_ctx *ctx)
{
	struct hantro_dev *vpu = ctx->dev;
	struct hantro_h264_dec_hw_ctx *h264_dec = &ctx->h264_dec;
	struct hantro_aux_buf *priv = &h264_dec->priv;

	dma_free_coherent(vpu->dev, priv->size, priv->cpu, priv->dma);
}