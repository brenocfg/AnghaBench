#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct cqspi_st {int /*<<< orphan*/  clk; scalar_t__ rx_chan; TYPE_2__* f_pdata; } ;
struct TYPE_3__ {int /*<<< orphan*/  mtd; } ;
struct TYPE_4__ {TYPE_1__ nor; scalar_t__ registered; } ;

/* Variables and functions */
 int CQSPI_MAX_CHIPSELECT ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cqspi_controller_enable (struct cqspi_st*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (scalar_t__) ; 
 int /*<<< orphan*/  mtd_device_unregister (int /*<<< orphan*/ *) ; 
 struct cqspi_st* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cqspi_remove(struct platform_device *pdev)
{
	struct cqspi_st *cqspi = platform_get_drvdata(pdev);
	int i;

	for (i = 0; i < CQSPI_MAX_CHIPSELECT; i++)
		if (cqspi->f_pdata[i].registered)
			mtd_device_unregister(&cqspi->f_pdata[i].nor.mtd);

	cqspi_controller_enable(cqspi, 0);

	if (cqspi->rx_chan)
		dma_release_channel(cqspi->rx_chan);

	clk_disable_unprepare(cqspi->clk);

	pm_runtime_put_sync(&pdev->dev);
	pm_runtime_disable(&pdev->dev);

	return 0;
}