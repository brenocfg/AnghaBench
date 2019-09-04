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
struct platform_device {int dummy; } ;
struct mv_cesa_engine {int /*<<< orphan*/  sram_dma; scalar_t__ sram; scalar_t__ pool; } ;
struct mv_cesa_dev {int /*<<< orphan*/  sram_size; int /*<<< orphan*/  dev; struct mv_cesa_engine* engines; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  dma_unmap_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_pool_free (scalar_t__,unsigned long,int /*<<< orphan*/ ) ; 
 struct mv_cesa_dev* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static void mv_cesa_put_sram(struct platform_device *pdev, int idx)
{
	struct mv_cesa_dev *cesa = platform_get_drvdata(pdev);
	struct mv_cesa_engine *engine = &cesa->engines[idx];

	if (engine->pool)
		gen_pool_free(engine->pool, (unsigned long)engine->sram,
			      cesa->sram_size);
	else
		dma_unmap_resource(cesa->dev, engine->sram_dma,
				   cesa->sram_size, DMA_BIDIRECTIONAL, 0);
}