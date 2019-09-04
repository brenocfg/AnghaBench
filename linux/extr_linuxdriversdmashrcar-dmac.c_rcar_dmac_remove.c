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
struct rcar_dmac {int /*<<< orphan*/  engine; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_async_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_dma_controller_free (int /*<<< orphan*/ ) ; 
 struct rcar_dmac* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_1__*) ; 

__attribute__((used)) static int rcar_dmac_remove(struct platform_device *pdev)
{
	struct rcar_dmac *dmac = platform_get_drvdata(pdev);

	of_dma_controller_free(pdev->dev.of_node);
	dma_async_device_unregister(&dmac->engine);

	pm_runtime_disable(&pdev->dev);

	return 0;
}