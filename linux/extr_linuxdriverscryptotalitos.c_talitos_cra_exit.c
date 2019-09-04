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
struct talitos_ctx {scalar_t__ keylen; int /*<<< orphan*/  dma_key; struct device* dev; } ;
struct device {int dummy; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 struct talitos_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void talitos_cra_exit(struct crypto_tfm *tfm)
{
	struct talitos_ctx *ctx = crypto_tfm_ctx(tfm);
	struct device *dev = ctx->dev;

	if (ctx->keylen)
		dma_unmap_single(dev, ctx->dma_key, ctx->keylen, DMA_TO_DEVICE);
}