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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct gpmi_nand_data {int /*<<< orphan*/  nand; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpmi_free_dma_buffer (struct gpmi_nand_data*) ; 
 int /*<<< orphan*/  nand_release (int /*<<< orphan*/ *) ; 
 struct gpmi_nand_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_resources (struct gpmi_nand_data*) ; 

__attribute__((used)) static int gpmi_nand_remove(struct platform_device *pdev)
{
	struct gpmi_nand_data *this = platform_get_drvdata(pdev);

	pm_runtime_put_sync(&pdev->dev);
	pm_runtime_disable(&pdev->dev);

	nand_release(&this->nand);
	gpmi_free_dma_buffer(this);
	release_resources(this);
	return 0;
}