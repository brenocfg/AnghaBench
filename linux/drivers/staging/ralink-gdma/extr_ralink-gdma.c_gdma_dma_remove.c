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
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct gdma_dma_dev {int /*<<< orphan*/  ddev; int /*<<< orphan*/  task; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_async_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_dma_controller_free (int /*<<< orphan*/ ) ; 
 struct gdma_dma_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gdma_dma_remove(struct platform_device *pdev)
{
	struct gdma_dma_dev *dma_dev = platform_get_drvdata(pdev);

	tasklet_kill(&dma_dev->task);
	of_dma_controller_free(pdev->dev.of_node);
	dma_async_device_unregister(&dma_dev->ddev);

	return 0;
}