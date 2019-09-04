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
struct iio_dev {int dummy; } ;
struct i2c_client {scalar_t__ irq; int /*<<< orphan*/  dev; } ;
struct ak8975_data {scalar_t__ eoc_gpio; int /*<<< orphan*/ * asa; TYPE_1__* def; int /*<<< orphan*/ * raw_to_gauss; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* raw_to_gauss ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/ * ctrl_regs; } ;

/* Variables and functions */
 size_t ASA_BASE ; 
 int /*<<< orphan*/  FUSE_ROM ; 
 int /*<<< orphan*/  POWER_DOWN ; 
 int ak8975_set_mode (struct ak8975_data*,int /*<<< orphan*/ ) ; 
 int ak8975_setup_irq (struct ak8975_data*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct iio_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_smbus_read_i2c_block_data_or_emulated (struct i2c_client*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct ak8975_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ak8975_setup(struct i2c_client *client)
{
	struct iio_dev *indio_dev = i2c_get_clientdata(client);
	struct ak8975_data *data = iio_priv(indio_dev);
	int ret;

	/* Write the fused rom access mode. */
	ret = ak8975_set_mode(data, FUSE_ROM);
	if (ret < 0) {
		dev_err(&client->dev, "Error in setting fuse access mode\n");
		return ret;
	}

	/* Get asa data and store in the device data. */
	ret = i2c_smbus_read_i2c_block_data_or_emulated(
			client, data->def->ctrl_regs[ASA_BASE],
			3, data->asa);
	if (ret < 0) {
		dev_err(&client->dev, "Not able to read asa data\n");
		return ret;
	}

	/* After reading fuse ROM data set power-down mode */
	ret = ak8975_set_mode(data, POWER_DOWN);
	if (ret < 0) {
		dev_err(&client->dev, "Error in setting power-down mode\n");
		return ret;
	}

	if (data->eoc_gpio > 0 || client->irq > 0) {
		ret = ak8975_setup_irq(data);
		if (ret < 0) {
			dev_err(&client->dev,
				"Error setting data ready interrupt\n");
			return ret;
		}
	}

	data->raw_to_gauss[0] = data->def->raw_to_gauss(data->asa[0]);
	data->raw_to_gauss[1] = data->def->raw_to_gauss(data->asa[1]);
	data->raw_to_gauss[2] = data->def->raw_to_gauss(data->asa[2]);

	return 0;
}