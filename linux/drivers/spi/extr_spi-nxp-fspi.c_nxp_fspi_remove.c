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
struct nxp_fspi {int /*<<< orphan*/  lock; scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ FSPI_MCR0 ; 
 int /*<<< orphan*/  FSPI_MCR0_MDIS ; 
 int /*<<< orphan*/  fspi_writel (struct nxp_fspi*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nxp_fspi_clk_disable_unprep (struct nxp_fspi*) ; 
 struct nxp_fspi* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int nxp_fspi_remove(struct platform_device *pdev)
{
	struct nxp_fspi *f = platform_get_drvdata(pdev);

	/* disable the hardware */
	fspi_writel(f, FSPI_MCR0_MDIS, f->iobase + FSPI_MCR0);

	nxp_fspi_clk_disable_unprep(f);

	mutex_destroy(&f->lock);

	return 0;
}