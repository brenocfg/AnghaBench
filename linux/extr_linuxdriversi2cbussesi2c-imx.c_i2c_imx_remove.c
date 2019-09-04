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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct imx_i2c_struct {int /*<<< orphan*/  clk; int /*<<< orphan*/  clk_change_nb; scalar_t__ dma; TYPE_1__ adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX_I2C_I2CR ; 
 int /*<<< orphan*/  IMX_I2C_I2SR ; 
 int /*<<< orphan*/  IMX_I2C_IADR ; 
 int /*<<< orphan*/  IMX_I2C_IFDR ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_notifier_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i2c_del_adapter (TYPE_1__*) ; 
 int /*<<< orphan*/  i2c_imx_dma_free (struct imx_i2c_struct*) ; 
 int /*<<< orphan*/  imx_i2c_write_reg (int /*<<< orphan*/ ,struct imx_i2c_struct*,int /*<<< orphan*/ ) ; 
 struct imx_i2c_struct* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i2c_imx_remove(struct platform_device *pdev)
{
	struct imx_i2c_struct *i2c_imx = platform_get_drvdata(pdev);
	int ret;

	ret = pm_runtime_get_sync(&pdev->dev);
	if (ret < 0)
		return ret;

	/* remove adapter */
	dev_dbg(&i2c_imx->adapter.dev, "adapter removed\n");
	i2c_del_adapter(&i2c_imx->adapter);

	if (i2c_imx->dma)
		i2c_imx_dma_free(i2c_imx);

	/* setup chip registers to defaults */
	imx_i2c_write_reg(0, i2c_imx, IMX_I2C_IADR);
	imx_i2c_write_reg(0, i2c_imx, IMX_I2C_IFDR);
	imx_i2c_write_reg(0, i2c_imx, IMX_I2C_I2CR);
	imx_i2c_write_reg(0, i2c_imx, IMX_I2C_I2SR);

	clk_notifier_unregister(i2c_imx->clk, &i2c_imx->clk_change_nb);
	clk_disable_unprepare(i2c_imx->clk);

	pm_runtime_put_noidle(&pdev->dev);
	pm_runtime_disable(&pdev->dev);

	return 0;
}