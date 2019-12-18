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
union i2c_smbus_data {int byte; int* block; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct i2c_adapter {int dummy; } ;
struct highlander_i2c_dev {int* buf; int buf_len; scalar_t__ base; int /*<<< orphan*/  dev; int /*<<< orphan*/  cmd_complete; } ;

/* Variables and functions */
 int EINVAL ; 
#define  I2C_SMBUS_BYTE_DATA 129 
#define  I2C_SMBUS_I2C_BLOCK_DATA 128 
 char I2C_SMBUS_READ ; 
 scalar_t__ SMMR ; 
 int SMMR_MODE0 ; 
 int SMMR_MODE1 ; 
 scalar_t__ SMSMADR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,char,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  highlander_i2c_command (struct highlander_i2c_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  highlander_i2c_done (struct highlander_i2c_dev*) ; 
 int highlander_i2c_read (struct highlander_i2c_dev*) ; 
 int highlander_i2c_write (struct highlander_i2c_dev*) ; 
 struct highlander_i2c_dev* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int ioread16 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite16 (int,scalar_t__) ; 

__attribute__((used)) static int highlander_i2c_smbus_xfer(struct i2c_adapter *adap, u16 addr,
				  unsigned short flags, char read_write,
				  u8 command, int size,
				  union i2c_smbus_data *data)
{
	struct highlander_i2c_dev *dev = i2c_get_adapdata(adap);
	u16 tmp;

	init_completion(&dev->cmd_complete);

	dev_dbg(dev->dev, "addr %04x, command %02x, read_write %d, size %d\n",
		addr, command, read_write, size);

	/*
	 * Set up the buffer and transfer size
	 */
	switch (size) {
	case I2C_SMBUS_BYTE_DATA:
		dev->buf = &data->byte;
		dev->buf_len = 1;
		break;
	case I2C_SMBUS_I2C_BLOCK_DATA:
		dev->buf = &data->block[1];
		dev->buf_len = data->block[0];
		break;
	default:
		dev_err(dev->dev, "unsupported command %d\n", size);
		return -EINVAL;
	}

	/*
	 * Encode the mode setting
	 */
	tmp = ioread16(dev->base + SMMR);
	tmp &= ~(SMMR_MODE0 | SMMR_MODE1);

	switch (dev->buf_len) {
	case 1:
		/* default */
		break;
	case 8:
		tmp |= SMMR_MODE0;
		break;
	case 16:
		tmp |= SMMR_MODE1;
		break;
	case 32:
		tmp |= (SMMR_MODE0 | SMMR_MODE1);
		break;
	default:
		dev_err(dev->dev, "unsupported xfer size %d\n", dev->buf_len);
		return -EINVAL;
	}

	iowrite16(tmp, dev->base + SMMR);

	/* Ensure we're in a sane state */
	highlander_i2c_done(dev);

	/* Set slave address */
	iowrite16((addr << 1) | read_write, dev->base + SMSMADR);

	highlander_i2c_command(dev, command, dev->buf_len);

	if (read_write == I2C_SMBUS_READ)
		return highlander_i2c_read(dev);
	else
		return highlander_i2c_write(dev);
}