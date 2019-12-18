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
struct hva_h264_ctx {scalar_t__ task; scalar_t__ rec_frame; scalar_t__ ref_frame; scalar_t__ seq_info; } ;
struct hva_ctx {scalar_t__ priv; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct device* ctx_to_dev (struct hva_ctx*) ; 
 int /*<<< orphan*/  devm_kfree (struct device*,struct hva_h264_ctx*) ; 
 int /*<<< orphan*/  hva_mem_free (struct hva_ctx*,scalar_t__) ; 

__attribute__((used)) static int hva_h264_close(struct hva_ctx *pctx)
{
	struct hva_h264_ctx *ctx = (struct hva_h264_ctx *)pctx->priv;
	struct device *dev = ctx_to_dev(pctx);

	if (ctx->seq_info)
		hva_mem_free(pctx, ctx->seq_info);

	if (ctx->ref_frame)
		hva_mem_free(pctx, ctx->ref_frame);

	if (ctx->rec_frame)
		hva_mem_free(pctx, ctx->rec_frame);

	if (ctx->task)
		hva_mem_free(pctx, ctx->task);

	devm_kfree(dev, ctx);

	return 0;
}