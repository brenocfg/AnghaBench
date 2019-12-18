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
struct bcm_qspi {int /*<<< orphan*/  master; int /*<<< orphan*/  dev_ids; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm_qspi_hw_uninit (struct bcm_qspi*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct bcm_qspi* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  spi_unregister_master (int /*<<< orphan*/ ) ; 

int bcm_qspi_remove(struct platform_device *pdev)
{
	struct bcm_qspi *qspi = platform_get_drvdata(pdev);

	bcm_qspi_hw_uninit(qspi);
	clk_disable_unprepare(qspi->clk);
	kfree(qspi->dev_ids);
	spi_unregister_master(qspi->master);

	return 0;
}