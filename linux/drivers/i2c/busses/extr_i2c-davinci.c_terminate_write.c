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
typedef  int u16 ;
struct davinci_i2c_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  terminate; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAVINCI_I2C_MDR_REG ; 
 int DAVINCI_I2C_MDR_RM ; 
 int DAVINCI_I2C_MDR_STP ; 
 int davinci_i2c_read_reg (struct davinci_i2c_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  davinci_i2c_write_reg (struct davinci_i2c_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void terminate_write(struct davinci_i2c_dev *dev)
{
	u16 w = davinci_i2c_read_reg(dev, DAVINCI_I2C_MDR_REG);
	w |= DAVINCI_I2C_MDR_RM | DAVINCI_I2C_MDR_STP;
	davinci_i2c_write_reg(dev, DAVINCI_I2C_MDR_REG, w);

	if (!dev->terminate)
		dev_dbg(dev->dev, "TDR IRQ while no data to send\n");
}