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
struct spi_controller {int dummy; } ;
struct platform_device {int dummy; } ;
struct atmel_qspi {int /*<<< orphan*/  pclk; int /*<<< orphan*/  qspick; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ QSPI_CR ; 
 int /*<<< orphan*/  QSPI_CR_QSPIDIS ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct spi_controller* platform_get_drvdata (struct platform_device*) ; 
 struct atmel_qspi* spi_controller_get_devdata (struct spi_controller*) ; 
 int /*<<< orphan*/  spi_unregister_controller (struct spi_controller*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int atmel_qspi_remove(struct platform_device *pdev)
{
	struct spi_controller *ctrl = platform_get_drvdata(pdev);
	struct atmel_qspi *aq = spi_controller_get_devdata(ctrl);

	spi_unregister_controller(ctrl);
	writel_relaxed(QSPI_CR_QSPIDIS, aq->regs + QSPI_CR);
	clk_disable_unprepare(aq->qspick);
	clk_disable_unprepare(aq->pclk);
	return 0;
}