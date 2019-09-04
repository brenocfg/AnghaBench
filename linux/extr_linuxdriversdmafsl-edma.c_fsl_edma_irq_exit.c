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
struct fsl_edma_engine {scalar_t__ txirq; scalar_t__ errirq; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ *,scalar_t__,struct fsl_edma_engine*) ; 

__attribute__((used)) static void fsl_edma_irq_exit(
		struct platform_device *pdev, struct fsl_edma_engine *fsl_edma)
{
	if (fsl_edma->txirq == fsl_edma->errirq) {
		devm_free_irq(&pdev->dev, fsl_edma->txirq, fsl_edma);
	} else {
		devm_free_irq(&pdev->dev, fsl_edma->txirq, fsl_edma);
		devm_free_irq(&pdev->dev, fsl_edma->errirq, fsl_edma);
	}
}