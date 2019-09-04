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
struct TYPE_2__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct dw_dma_chip {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_dma_remove (struct dw_dma_chip*) ; 
 int /*<<< orphan*/  of_dma_controller_free (scalar_t__) ; 
 struct dw_dma_chip* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_1__*) ; 

__attribute__((used)) static int dw_remove(struct platform_device *pdev)
{
	struct dw_dma_chip *chip = platform_get_drvdata(pdev);

	if (pdev->dev.of_node)
		of_dma_controller_free(pdev->dev.of_node);

	dw_dma_remove(chip);
	pm_runtime_disable(&pdev->dev);
	clk_disable_unprepare(chip->clk);

	return 0;
}