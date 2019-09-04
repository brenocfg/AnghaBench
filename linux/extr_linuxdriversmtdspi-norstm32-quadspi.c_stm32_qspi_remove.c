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
struct stm32_qspi {int /*<<< orphan*/  clk; int /*<<< orphan*/  lock; scalar_t__ io_base; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ QUADSPI_CR ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct stm32_qspi* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stm32_qspi_mtd_free (struct stm32_qspi*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int stm32_qspi_remove(struct platform_device *pdev)
{
	struct stm32_qspi *qspi = platform_get_drvdata(pdev);

	/* disable qspi */
	writel_relaxed(0, qspi->io_base + QUADSPI_CR);

	stm32_qspi_mtd_free(qspi);
	mutex_destroy(&qspi->lock);

	clk_disable_unprepare(qspi->clk);
	return 0;
}