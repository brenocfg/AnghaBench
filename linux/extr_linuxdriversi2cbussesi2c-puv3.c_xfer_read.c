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
struct i2c_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  I2C_DATACMD ; 
 unsigned char I2C_DATACMD_DAT_MASK ; 
 int I2C_DATACMD_READ ; 
 int I2C_DATACMD_WRITE ; 
 int /*<<< orphan*/  I2C_STATUS_RFNE ; 
 int /*<<< orphan*/  I2C_STATUS_TFNF ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  poll_status (int /*<<< orphan*/ ) ; 
 unsigned char readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xfer_read(struct i2c_adapter *adap, unsigned char *buf, int length)
{
	int i2c_reg = *buf;

	/* Read data */
	while (length--) {
		if (!poll_status(I2C_STATUS_TFNF)) {
			dev_dbg(&adap->dev, "Tx FIFO Not Full timeout\n");
			return -ETIMEDOUT;
		}

		/* send addr */
		writel(i2c_reg | I2C_DATACMD_WRITE, I2C_DATACMD);

		/* get ready to next write */
		i2c_reg++;

		/* send read CMD */
		writel(I2C_DATACMD_READ, I2C_DATACMD);

		/* wait until the Rx FIFO have available */
		if (!poll_status(I2C_STATUS_RFNE)) {
			dev_dbg(&adap->dev, "RXRDY timeout\n");
			return -ETIMEDOUT;
		}

		/* read the data to buf */
		*buf = (readl(I2C_DATACMD) & I2C_DATACMD_DAT_MASK);
		buf++;
	}

	return 0;
}