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
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;
struct lpi2c_imx_struct {TYPE_2__ adapter; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ LPI2C_MCR ; 
 unsigned int MCR_MEN ; 
 unsigned int MCR_RST ; 
 int lpi2c_imx_config (struct lpi2c_imx_struct*) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int lpi2c_imx_master_enable(struct lpi2c_imx_struct *lpi2c_imx)
{
	unsigned int temp;
	int ret;

	ret = pm_runtime_get_sync(lpi2c_imx->adapter.dev.parent);
	if (ret < 0)
		return ret;

	temp = MCR_RST;
	writel(temp, lpi2c_imx->base + LPI2C_MCR);
	writel(0, lpi2c_imx->base + LPI2C_MCR);

	ret = lpi2c_imx_config(lpi2c_imx);
	if (ret)
		goto rpm_put;

	temp = readl(lpi2c_imx->base + LPI2C_MCR);
	temp |= MCR_MEN;
	writel(temp, lpi2c_imx->base + LPI2C_MCR);

	return 0;

rpm_put:
	pm_runtime_mark_last_busy(lpi2c_imx->adapter.dev.parent);
	pm_runtime_put_autosuspend(lpi2c_imx->adapter.dev.parent);

	return ret;
}