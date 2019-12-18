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
struct fsl_qspi {int /*<<< orphan*/  lock; scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ QUADSPI_MCR ; 
 int QUADSPI_MCR_MDIS_MASK ; 
 scalar_t__ QUADSPI_RSER ; 
 int /*<<< orphan*/  fsl_qspi_clk_disable_unprep (struct fsl_qspi*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct fsl_qspi* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  qspi_writel (struct fsl_qspi*,int,scalar_t__) ; 

__attribute__((used)) static int fsl_qspi_remove(struct platform_device *pdev)
{
	struct fsl_qspi *q = platform_get_drvdata(pdev);

	/* disable the hardware */
	qspi_writel(q, QUADSPI_MCR_MDIS_MASK, q->iobase + QUADSPI_MCR);
	qspi_writel(q, 0x0, q->iobase + QUADSPI_RSER);

	fsl_qspi_clk_disable_unprep(q);

	mutex_destroy(&q->lock);

	return 0;
}