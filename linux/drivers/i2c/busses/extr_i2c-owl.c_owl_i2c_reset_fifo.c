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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct owl_i2c_dev {TYPE_1__ adap; scalar_t__ base; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 unsigned int OWL_I2C_FIFOCTL_RFR ; 
 unsigned int OWL_I2C_FIFOCTL_TFR ; 
 unsigned int OWL_I2C_MAX_RETRIES ; 
 scalar_t__ OWL_I2C_REG_FIFOCTL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  owl_i2c_update_reg (scalar_t__,unsigned int,int) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int owl_i2c_reset_fifo(struct owl_i2c_dev *i2c_dev)
{
	unsigned int val, timeout = 0;

	/* Reset FIFO */
	owl_i2c_update_reg(i2c_dev->base + OWL_I2C_REG_FIFOCTL,
			   OWL_I2C_FIFOCTL_RFR | OWL_I2C_FIFOCTL_TFR,
			   true);

	/* Wait 50ms for FIFO reset complete */
	do {
		val = readl(i2c_dev->base + OWL_I2C_REG_FIFOCTL);
		if (!(val & (OWL_I2C_FIFOCTL_RFR | OWL_I2C_FIFOCTL_TFR)))
			break;
		usleep_range(500, 1000);
	} while (timeout++ < OWL_I2C_MAX_RETRIES);

	if (timeout > OWL_I2C_MAX_RETRIES) {
		dev_err(&i2c_dev->adap.dev, "FIFO reset timeout\n");
		return -ETIMEDOUT;
	}

	return 0;
}