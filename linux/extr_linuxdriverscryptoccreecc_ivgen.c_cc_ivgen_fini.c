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
struct device {int dummy; } ;
struct cc_ivgen_ctx {int /*<<< orphan*/  pool; int /*<<< orphan*/  pool_meta_dma; scalar_t__ pool_meta; } ;
struct cc_drvdata {TYPE_1__* plat_dev; struct cc_ivgen_ctx* ivgen_handle; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC_IVPOOL_META_SIZE ; 
 int /*<<< orphan*/  NULL_SRAM_ADDR ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cc_ivgen_ctx*) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cc_ivgen_fini(struct cc_drvdata *drvdata)
{
	struct cc_ivgen_ctx *ivgen_ctx = drvdata->ivgen_handle;
	struct device *device = &drvdata->plat_dev->dev;

	if (!ivgen_ctx)
		return;

	if (ivgen_ctx->pool_meta) {
		memset(ivgen_ctx->pool_meta, 0, CC_IVPOOL_META_SIZE);
		dma_free_coherent(device, CC_IVPOOL_META_SIZE,
				  ivgen_ctx->pool_meta,
				  ivgen_ctx->pool_meta_dma);
	}

	ivgen_ctx->pool = NULL_SRAM_ADDR;

	/* release "this" context */
	kfree(ivgen_ctx);
}