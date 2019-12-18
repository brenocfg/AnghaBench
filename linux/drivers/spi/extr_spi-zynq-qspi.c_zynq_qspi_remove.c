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
struct zynq_qspi {int /*<<< orphan*/  pclk; int /*<<< orphan*/  refclk; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZYNQ_QSPI_ENABLE_OFFSET ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct zynq_qspi* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  zynq_qspi_write (struct zynq_qspi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zynq_qspi_remove(struct platform_device *pdev)
{
	struct zynq_qspi *xqspi = platform_get_drvdata(pdev);

	zynq_qspi_write(xqspi, ZYNQ_QSPI_ENABLE_OFFSET, 0);

	clk_disable_unprepare(xqspi->refclk);
	clk_disable_unprepare(xqspi->pclk);

	return 0;
}