#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mtd; } ;
struct atmel_qspi {int /*<<< orphan*/  clk; TYPE_1__ nor; } ;

/* Variables and functions */
 int /*<<< orphan*/  QSPI_CR ; 
 int /*<<< orphan*/  QSPI_CR_QSPIDIS ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtd_device_unregister (int /*<<< orphan*/ *) ; 
 struct atmel_qspi* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  qspi_writel (struct atmel_qspi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_qspi_remove(struct platform_device *pdev)
{
	struct atmel_qspi *aq = platform_get_drvdata(pdev);

	mtd_device_unregister(&aq->nor.mtd);
	qspi_writel(aq, QSPI_CR, QSPI_CR_QSPIDIS);
	clk_disable_unprepare(aq->clk);
	return 0;
}