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
typedef  int u32 ;
struct omap_sham_reqctx {int flags; int /*<<< orphan*/  digcnt; } ;
struct omap_sham_dev {int /*<<< orphan*/  req; } ;

/* Variables and functions */
 int FLAGS_MODE_MASK ; 
 int FLAGS_MODE_SHA1 ; 
 int /*<<< orphan*/  SHA_REG_CTRL ; 
 int SHA_REG_CTRL_ALGO ; 
 int SHA_REG_CTRL_ALGO_CONST ; 
 int SHA_REG_CTRL_CLOSE_HASH ; 
 int SHA_REG_CTRL_LENGTH ; 
 int /*<<< orphan*/  SHA_REG_DIGCNT (struct omap_sham_dev*) ; 
 int /*<<< orphan*/  SHA_REG_MASK (struct omap_sham_dev*) ; 
 int SHA_REG_MASK_DMA_EN ; 
 int SHA_REG_MASK_IT_EN ; 
 struct omap_sham_reqctx* ahash_request_ctx (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_sham_write (struct omap_sham_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_sham_write_mask (struct omap_sham_dev*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void omap_sham_write_ctrl_omap2(struct omap_sham_dev *dd, size_t length,
				 int final, int dma)
{
	struct omap_sham_reqctx *ctx = ahash_request_ctx(dd->req);
	u32 val = length << 5, mask;

	if (likely(ctx->digcnt))
		omap_sham_write(dd, SHA_REG_DIGCNT(dd), ctx->digcnt);

	omap_sham_write_mask(dd, SHA_REG_MASK(dd),
		SHA_REG_MASK_IT_EN | (dma ? SHA_REG_MASK_DMA_EN : 0),
		SHA_REG_MASK_IT_EN | SHA_REG_MASK_DMA_EN);
	/*
	 * Setting ALGO_CONST only for the first iteration
	 * and CLOSE_HASH only for the last one.
	 */
	if ((ctx->flags & FLAGS_MODE_MASK) == FLAGS_MODE_SHA1)
		val |= SHA_REG_CTRL_ALGO;
	if (!ctx->digcnt)
		val |= SHA_REG_CTRL_ALGO_CONST;
	if (final)
		val |= SHA_REG_CTRL_CLOSE_HASH;

	mask = SHA_REG_CTRL_ALGO_CONST | SHA_REG_CTRL_CLOSE_HASH |
			SHA_REG_CTRL_ALGO | SHA_REG_CTRL_LENGTH;

	omap_sham_write_mask(dd, SHA_REG_CTRL, val, mask);
}