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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct flexrm_mbox {int /*<<< orphan*/  bd_pool; int /*<<< orphan*/  cmpl_pool; int /*<<< orphan*/  root; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ ) ; 
 struct flexrm_mbox* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_msi_domain_free_irqs (struct device*) ; 

__attribute__((used)) static int flexrm_mbox_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct flexrm_mbox *mbox = platform_get_drvdata(pdev);

	debugfs_remove_recursive(mbox->root);

	platform_msi_domain_free_irqs(dev);

	dma_pool_destroy(mbox->cmpl_pool);
	dma_pool_destroy(mbox->bd_pool);

	return 0;
}