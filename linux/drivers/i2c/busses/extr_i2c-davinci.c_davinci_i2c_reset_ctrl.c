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
typedef  int /*<<< orphan*/  u16 ;
struct davinci_i2c_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAVINCI_I2C_MDR_IRS ; 
 int /*<<< orphan*/  DAVINCI_I2C_MDR_REG ; 
 int /*<<< orphan*/  davinci_i2c_read_reg (struct davinci_i2c_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  davinci_i2c_write_reg (struct davinci_i2c_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void davinci_i2c_reset_ctrl(struct davinci_i2c_dev *i2c_dev,
								int val)
{
	u16 w;

	w = davinci_i2c_read_reg(i2c_dev, DAVINCI_I2C_MDR_REG);
	if (!val)	/* put I2C into reset */
		w &= ~DAVINCI_I2C_MDR_IRS;
	else		/* take I2C out of reset */
		w |= DAVINCI_I2C_MDR_IRS;

	davinci_i2c_write_reg(i2c_dev, DAVINCI_I2C_MDR_REG, w);
}