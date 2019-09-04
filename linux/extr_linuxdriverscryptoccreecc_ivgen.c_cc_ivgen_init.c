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
struct cc_ivgen_ctx {scalar_t__ pool; int /*<<< orphan*/  pool_meta; int /*<<< orphan*/  pool_meta_dma; } ;
struct cc_drvdata {struct cc_ivgen_ctx* ivgen_handle; TYPE_1__* plat_dev; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC_IVPOOL_META_SIZE ; 
 int /*<<< orphan*/  CC_IVPOOL_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NULL_SRAM_ADDR ; 
 int cc_init_iv_sram (struct cc_drvdata*) ; 
 int /*<<< orphan*/  cc_ivgen_fini (struct cc_drvdata*) ; 
 scalar_t__ cc_sram_alloc (struct cc_drvdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dma_alloc_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct cc_ivgen_ctx* kzalloc (int,int /*<<< orphan*/ ) ; 

int cc_ivgen_init(struct cc_drvdata *drvdata)
{
	struct cc_ivgen_ctx *ivgen_ctx;
	struct device *device = &drvdata->plat_dev->dev;
	int rc;

	/* Allocate "this" context */
	ivgen_ctx = kzalloc(sizeof(*ivgen_ctx), GFP_KERNEL);
	if (!ivgen_ctx)
		return -ENOMEM;

	/* Allocate pool's header for initial enc. key/IV */
	ivgen_ctx->pool_meta = dma_alloc_coherent(device, CC_IVPOOL_META_SIZE,
						  &ivgen_ctx->pool_meta_dma,
						  GFP_KERNEL);
	if (!ivgen_ctx->pool_meta) {
		dev_err(device, "Not enough memory to allocate DMA of pool_meta (%u B)\n",
			CC_IVPOOL_META_SIZE);
		rc = -ENOMEM;
		goto out;
	}
	/* Allocate IV pool in SRAM */
	ivgen_ctx->pool = cc_sram_alloc(drvdata, CC_IVPOOL_SIZE);
	if (ivgen_ctx->pool == NULL_SRAM_ADDR) {
		dev_err(device, "SRAM pool exhausted\n");
		rc = -ENOMEM;
		goto out;
	}

	drvdata->ivgen_handle = ivgen_ctx;

	return cc_init_iv_sram(drvdata);

out:
	cc_ivgen_fini(drvdata);
	return rc;
}