#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int dummy; } ;
struct mv_cesa_engine {int /*<<< orphan*/  sram_dma; scalar_t__ sram; int /*<<< orphan*/ * pool; } ;
struct mv_cesa_dev {scalar_t__ sram_size; TYPE_2__* dev; TYPE_1__* caps; struct mv_cesa_engine* engines; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_5__ {int nengines; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 scalar_t__ devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 int /*<<< orphan*/  dma_map_resource (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ gen_pool_dma_alloc (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * of_gen_pool_get (int /*<<< orphan*/ ,char*,int) ; 
 struct mv_cesa_dev* platform_get_drvdata (struct platform_device*) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ resource_size (struct resource*) ; 

__attribute__((used)) static int mv_cesa_get_sram(struct platform_device *pdev, int idx)
{
	struct mv_cesa_dev *cesa = platform_get_drvdata(pdev);
	struct mv_cesa_engine *engine = &cesa->engines[idx];
	const char *res_name = "sram";
	struct resource *res;

	engine->pool = of_gen_pool_get(cesa->dev->of_node,
				       "marvell,crypto-srams", idx);
	if (engine->pool) {
		engine->sram = gen_pool_dma_alloc(engine->pool,
						  cesa->sram_size,
						  &engine->sram_dma);
		if (engine->sram)
			return 0;

		engine->pool = NULL;
		return -ENOMEM;
	}

	if (cesa->caps->nengines > 1) {
		if (!idx)
			res_name = "sram0";
		else
			res_name = "sram1";
	}

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM,
					   res_name);
	if (!res || resource_size(res) < cesa->sram_size)
		return -EINVAL;

	engine->sram = devm_ioremap_resource(cesa->dev, res);
	if (IS_ERR(engine->sram))
		return PTR_ERR(engine->sram);

	engine->sram_dma = dma_map_resource(cesa->dev, res->start,
					    cesa->sram_size,
					    DMA_BIDIRECTIONAL, 0);
	if (dma_mapping_error(cesa->dev, engine->sram_dma))
		return -ENOMEM;

	return 0;
}