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
struct xlp9xx_i2c_dev {int /*<<< orphan*/  adapter; int /*<<< orphan*/  irq; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XLP9XX_I2C_CTRL ; 
 int /*<<< orphan*/  XLP9XX_I2C_INTEN ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 struct xlp9xx_i2c_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xlp9xx_write_i2c_reg (struct xlp9xx_i2c_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xlp9xx_i2c_remove(struct platform_device *pdev)
{
	struct xlp9xx_i2c_dev *priv;

	priv = platform_get_drvdata(pdev);
	xlp9xx_write_i2c_reg(priv, XLP9XX_I2C_INTEN, 0);
	synchronize_irq(priv->irq);
	i2c_del_adapter(&priv->adapter);
	xlp9xx_write_i2c_reg(priv, XLP9XX_I2C_CTRL, 0);

	return 0;
}