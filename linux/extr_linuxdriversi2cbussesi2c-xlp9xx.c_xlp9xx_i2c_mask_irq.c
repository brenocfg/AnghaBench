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
struct xlp9xx_i2c_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XLP9XX_I2C_INTEN ; 
 int xlp9xx_read_i2c_reg (struct xlp9xx_i2c_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xlp9xx_write_i2c_reg (struct xlp9xx_i2c_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xlp9xx_i2c_mask_irq(struct xlp9xx_i2c_dev *priv, u32 mask)
{
	u32 inten;

	inten = xlp9xx_read_i2c_reg(priv, XLP9XX_I2C_INTEN) & ~mask;
	xlp9xx_write_i2c_reg(priv, XLP9XX_I2C_INTEN, inten);
}