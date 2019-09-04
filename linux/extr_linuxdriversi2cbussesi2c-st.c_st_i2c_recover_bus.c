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
struct st_i2c_dev {scalar_t__ base; int /*<<< orphan*/  dev; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ SSC_CTL ; 
 int SSC_CTL_EN ; 
 int SSC_CTL_EN_RX_FIFO ; 
 int SSC_CTL_EN_TX_FIFO ; 
 int SSC_CTL_MS ; 
 scalar_t__ SSC_I2C ; 
 int SSC_I2C_I2CM ; 
 scalar_t__ SSC_IEN ; 
 scalar_t__ SSC_TBUF ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct st_i2c_dev* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  st_i2c_clr_bits (scalar_t__,int) ; 
 int /*<<< orphan*/  st_i2c_hw_config (struct st_i2c_dev*) ; 
 int /*<<< orphan*/  st_i2c_set_bits (scalar_t__,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int st_i2c_recover_bus(struct i2c_adapter *i2c_adap)
{
	struct st_i2c_dev *i2c_dev = i2c_get_adapdata(i2c_adap);
	u32 ctl;

	dev_dbg(i2c_dev->dev, "Trying to recover bus\n");

	/*
	 * SSP IP is dual role SPI/I2C to generate 9 clock pulses
	 * we switch to SPI node, 9 bit words and write a 0. This
	 * has been validate with a oscilloscope and is easier
	 * than switching to GPIO mode.
	 */

	/* Disable interrupts */
	writel_relaxed(0, i2c_dev->base + SSC_IEN);

	st_i2c_hw_config(i2c_dev);

	ctl = SSC_CTL_EN | SSC_CTL_MS |	SSC_CTL_EN_RX_FIFO | SSC_CTL_EN_TX_FIFO;
	st_i2c_set_bits(i2c_dev->base + SSC_CTL, ctl);

	st_i2c_clr_bits(i2c_dev->base + SSC_I2C, SSC_I2C_I2CM);
	usleep_range(8000, 10000);

	writel_relaxed(0, i2c_dev->base + SSC_TBUF);
	usleep_range(2000, 4000);
	st_i2c_set_bits(i2c_dev->base + SSC_I2C, SSC_I2C_I2CM);

	return 0;
}