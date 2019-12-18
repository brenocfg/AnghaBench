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
struct mn88472_dev {int i2c_write_max; int ts_mode; int ts_clk; int active; int /*<<< orphan*/ * regmap; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct firmware {int size; int /*<<< orphan*/ * data; } ;
struct dvb_frontend {struct i2c_client* demodulator_priv; } ;

/* Variables and functions */
 int EINVAL ; 
#define  FIXED_TS_CLOCK 131 
 char* MN88472_FIRMWARE ; 
#define  PARALLEL_TS_MODE 130 
#define  SERIAL_TS_MODE 129 
#define  VARIABLE_TS_CLOCK 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char const*) ; 
 struct mn88472_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int min (int,int) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mn88472_init(struct dvb_frontend *fe)
{
	struct i2c_client *client = fe->demodulator_priv;
	struct mn88472_dev *dev = i2c_get_clientdata(client);
	int ret, len, rem;
	unsigned int utmp;
	const struct firmware *firmware;
	const char *name = MN88472_FIRMWARE;

	dev_dbg(&client->dev, "\n");

	/* Power up */
	ret = regmap_write(dev->regmap[2], 0x05, 0x00);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap[2], 0x0b, 0x00);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap[2], 0x0c, 0x00);
	if (ret)
		goto err;

	/* Check if firmware is already running */
	ret = regmap_read(dev->regmap[0], 0xf5, &utmp);
	if (ret)
		goto err;
	if (!(utmp & 0x01))
		goto warm;

	ret = request_firmware(&firmware, name, &client->dev);
	if (ret) {
		dev_err(&client->dev, "firmware file '%s' not found\n", name);
		goto err;
	}

	dev_info(&client->dev, "downloading firmware from file '%s'\n", name);

	ret = regmap_write(dev->regmap[0], 0xf5, 0x03);
	if (ret)
		goto err_release_firmware;

	for (rem = firmware->size; rem > 0; rem -= (dev->i2c_write_max - 1)) {
		len = min(dev->i2c_write_max - 1, rem);
		ret = regmap_bulk_write(dev->regmap[0], 0xf6,
					&firmware->data[firmware->size - rem],
					len);
		if (ret) {
			dev_err(&client->dev, "firmware download failed %d\n",
				ret);
			goto err_release_firmware;
		}
	}

	/* Parity check of firmware */
	ret = regmap_read(dev->regmap[0], 0xf8, &utmp);
	if (ret)
		goto err_release_firmware;
	if (utmp & 0x10) {
		ret = -EINVAL;
		dev_err(&client->dev, "firmware did not run\n");
		goto err_release_firmware;
	}

	ret = regmap_write(dev->regmap[0], 0xf5, 0x00);
	if (ret)
		goto err_release_firmware;

	release_firmware(firmware);
warm:
	/* TS config */
	switch (dev->ts_mode) {
	case SERIAL_TS_MODE:
		utmp = 0x1d;
		break;
	case PARALLEL_TS_MODE:
		utmp = 0x00;
		break;
	default:
		ret = -EINVAL;
		goto err;
	}
	ret = regmap_write(dev->regmap[2], 0x08, utmp);
	if (ret)
		goto err;

	switch (dev->ts_clk) {
	case VARIABLE_TS_CLOCK:
		utmp = 0xe3;
		break;
	case FIXED_TS_CLOCK:
		utmp = 0xe1;
		break;
	default:
		ret = -EINVAL;
		goto err;
	}
	ret = regmap_write(dev->regmap[0], 0xd9, utmp);
	if (ret)
		goto err;

	dev->active = true;

	return 0;
err_release_firmware:
	release_firmware(firmware);
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}