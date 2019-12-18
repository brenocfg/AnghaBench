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
union i2c_smbus_data {int /*<<< orphan*/  byte; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct i2c_adapter {int dummy; } ;
struct cht_wc_i2c_adap {int io_error; int done; int /*<<< orphan*/  adap_lock; int /*<<< orphan*/  read_data; int /*<<< orphan*/  wait; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHT_WC_I2C_CLIENT_ADDR ; 
 int /*<<< orphan*/  CHT_WC_I2C_CTRL ; 
 int /*<<< orphan*/  CHT_WC_I2C_CTRL_RD ; 
 int /*<<< orphan*/  CHT_WC_I2C_CTRL_WR ; 
 int /*<<< orphan*/  CHT_WC_I2C_REG_OFFSET ; 
 int /*<<< orphan*/  CHT_WC_I2C_WRDATA ; 
 int EIO ; 
 int ETIMEDOUT ; 
 char I2C_SMBUS_READ ; 
 char I2C_SMBUS_WRITE ; 
 int /*<<< orphan*/  cht_wc_i2c_adap_thread_handler (int /*<<< orphan*/ ,struct cht_wc_i2c_adap*) ; 
 struct cht_wc_i2c_adap* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cht_wc_i2c_adap_smbus_xfer(struct i2c_adapter *_adap, u16 addr,
				      unsigned short flags, char read_write,
				      u8 command, int size,
				      union i2c_smbus_data *data)
{
	struct cht_wc_i2c_adap *adap = i2c_get_adapdata(_adap);
	int ret;

	mutex_lock(&adap->adap_lock);
	adap->io_error = false;
	adap->done = false;
	mutex_unlock(&adap->adap_lock);

	ret = regmap_write(adap->regmap, CHT_WC_I2C_CLIENT_ADDR, addr);
	if (ret)
		return ret;

	if (read_write == I2C_SMBUS_WRITE) {
		ret = regmap_write(adap->regmap, CHT_WC_I2C_WRDATA, data->byte);
		if (ret)
			return ret;
	}

	ret = regmap_write(adap->regmap, CHT_WC_I2C_REG_OFFSET, command);
	if (ret)
		return ret;

	ret = regmap_write(adap->regmap, CHT_WC_I2C_CTRL,
			   (read_write == I2C_SMBUS_WRITE) ?
			   CHT_WC_I2C_CTRL_WR : CHT_WC_I2C_CTRL_RD);
	if (ret)
		return ret;

	ret = wait_event_timeout(adap->wait, adap->done, msecs_to_jiffies(30));
	if (ret == 0) {
		/*
		 * The CHT GPIO controller serializes all IRQs, sometimes
		 * causing significant delays, check status manually.
		 */
		cht_wc_i2c_adap_thread_handler(0, adap);
		if (!adap->done)
			return -ETIMEDOUT;
	}

	ret = 0;
	mutex_lock(&adap->adap_lock);
	if (adap->io_error)
		ret = -EIO;
	else if (read_write == I2C_SMBUS_READ)
		data->byte = adap->read_data;
	mutex_unlock(&adap->adap_lock);

	return ret;
}