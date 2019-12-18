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
struct bcm2835_i2c_dev {scalar_t__ msg_buf_remaining; int /*<<< orphan*/ * msg_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_I2C_FIFO ; 
 int /*<<< orphan*/  BCM2835_I2C_S ; 
 int BCM2835_I2C_S_TXD ; 
 int bcm2835_i2c_readl (struct bcm2835_i2c_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_i2c_writel (struct bcm2835_i2c_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm2835_fill_txfifo(struct bcm2835_i2c_dev *i2c_dev)
{
	u32 val;

	while (i2c_dev->msg_buf_remaining) {
		val = bcm2835_i2c_readl(i2c_dev, BCM2835_I2C_S);
		if (!(val & BCM2835_I2C_S_TXD))
			break;
		bcm2835_i2c_writel(i2c_dev, BCM2835_I2C_FIFO,
				   *i2c_dev->msg_buf);
		i2c_dev->msg_buf++;
		i2c_dev->msg_buf_remaining--;
	}
}