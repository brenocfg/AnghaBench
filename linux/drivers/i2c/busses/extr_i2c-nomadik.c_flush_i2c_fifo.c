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
struct TYPE_4__ {unsigned long timeout; } ;
struct nmk_i2c_dev {TYPE_1__* adev; scalar_t__ virtbase; TYPE_2__ adap; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ I2C_CR ; 
 int I2C_CR_FRX ; 
 int I2C_CR_FTX ; 
 int LOOP_ATTEMPTS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 unsigned long jiffies ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int flush_i2c_fifo(struct nmk_i2c_dev *dev)
{
#define LOOP_ATTEMPTS 10
	int i;
	unsigned long timeout;

	/*
	 * flush the transmit and receive FIFO. The flushing
	 * operation takes several cycles before to be completed.
	 * On the completion, the I2C internal logic clears these
	 * bits, until then no one must access Tx, Rx FIFO and
	 * should poll on these bits waiting for the completion.
	 */
	writel((I2C_CR_FTX | I2C_CR_FRX), dev->virtbase + I2C_CR);

	for (i = 0; i < LOOP_ATTEMPTS; i++) {
		timeout = jiffies + dev->adap.timeout;

		while (!time_after(jiffies, timeout)) {
			if ((readl(dev->virtbase + I2C_CR) &
				(I2C_CR_FTX | I2C_CR_FRX)) == 0)
					return 0;
		}
	}

	dev_err(&dev->adev->dev,
		"flushing operation timed out giving up after %d attempts",
		LOOP_ATTEMPTS);

	return -ETIMEDOUT;
}