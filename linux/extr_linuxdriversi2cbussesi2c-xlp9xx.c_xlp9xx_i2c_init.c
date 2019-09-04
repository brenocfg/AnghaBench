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
typedef  int u32 ;
struct xlp9xx_i2c_dev {int /*<<< orphan*/  clk_hz; int /*<<< orphan*/  ip_clk_hz; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLP9XX_I2C_CTRL ; 
 int XLP9XX_I2C_CTRL_EN ; 
 int XLP9XX_I2C_CTRL_MASTER ; 
 int XLP9XX_I2C_CTRL_RST ; 
 int /*<<< orphan*/  XLP9XX_I2C_DIV ; 
 int /*<<< orphan*/  XLP9XX_I2C_INTEN ; 
 int /*<<< orphan*/  xlp9xx_write_i2c_reg (struct xlp9xx_i2c_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int xlp9xx_i2c_init(struct xlp9xx_i2c_dev *priv)
{
	u32 prescale;

	/*
	 * The controller uses 5 * SCL clock internally.
	 * So prescale value should be divided by 5.
	 */
	prescale = DIV_ROUND_UP(priv->ip_clk_hz, priv->clk_hz);
	prescale = ((prescale - 8) / 5) - 1;
	xlp9xx_write_i2c_reg(priv, XLP9XX_I2C_CTRL, XLP9XX_I2C_CTRL_RST);
	xlp9xx_write_i2c_reg(priv, XLP9XX_I2C_CTRL, XLP9XX_I2C_CTRL_EN |
			     XLP9XX_I2C_CTRL_MASTER);
	xlp9xx_write_i2c_reg(priv, XLP9XX_I2C_DIV, prescale);
	xlp9xx_write_i2c_reg(priv, XLP9XX_I2C_INTEN, 0);

	return 0;
}