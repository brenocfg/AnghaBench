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
 int EIO ; 
 int XLP9XX_I2C_BUSY_TIMEOUT ; 
 int /*<<< orphan*/  XLP9XX_I2C_STATUS ; 
 int XLP9XX_I2C_STATUS_BUSY ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int xlp9xx_read_i2c_reg (struct xlp9xx_i2c_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xlp9xx_i2c_check_bus_status(struct xlp9xx_i2c_dev *priv)
{
	u32 status;
	u32 busy_timeout = XLP9XX_I2C_BUSY_TIMEOUT;

	while (busy_timeout) {
		status = xlp9xx_read_i2c_reg(priv, XLP9XX_I2C_STATUS);
		if ((status & XLP9XX_I2C_STATUS_BUSY) == 0)
			break;

		busy_timeout--;
		usleep_range(1000, 1100);
	}

	if (!busy_timeout)
		return -EIO;

	return 0;
}