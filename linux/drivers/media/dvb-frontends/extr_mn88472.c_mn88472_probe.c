#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct regmap_config {int reg_bits; int val_bits; } ;
struct TYPE_13__ {int len; } ;
struct TYPE_12__ {int len; } ;
struct TYPE_11__ {int len; } ;
struct TYPE_10__ {int len; } ;
struct dtv_frontend_properties {TYPE_5__ block_count; TYPE_4__ block_error; TYPE_3__ cnr; TYPE_2__ strength; } ;
struct TYPE_9__ {struct dtv_frontend_properties dtv_property_cache; struct i2c_client* demodulator_priv; int /*<<< orphan*/  ops; } ;
struct mn88472_dev {struct i2c_client** regmap; struct i2c_client** client; TYPE_1__ fe; int /*<<< orphan*/  ts_clk; int /*<<< orphan*/  ts_mode; int /*<<< orphan*/  clk; scalar_t__ i2c_write_max; } ;
struct mn88472_config {int /*<<< orphan*/  get_dvb_frontend; TYPE_1__** fe; int /*<<< orphan*/  ts_clock; int /*<<< orphan*/  ts_mode; int /*<<< orphan*/  xtal; scalar_t__ i2c_wr_max; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_14__ {struct mn88472_config* platform_data; } ;
struct i2c_client {TYPE_6__ dev; int /*<<< orphan*/  adapter; } ;
struct dvb_frontend_ops {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct i2c_client*) ; 
 int PTR_ERR (struct i2c_client*) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_6__*,char*,...) ; 
 int /*<<< orphan*/  dev_err (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_6__*,char*) ; 
 void* i2c_new_dummy_device (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct mn88472_dev*) ; 
 int /*<<< orphan*/  i2c_unregister_device (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (struct mn88472_dev*) ; 
 struct mn88472_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mn88472_get_dvb_frontend ; 
 int /*<<< orphan*/  mn88472_ops ; 
 int /*<<< orphan*/  regmap_exit (struct i2c_client*) ; 
 void* regmap_init_i2c (struct i2c_client*,struct regmap_config const*) ; 
 int regmap_read (struct i2c_client*,int,unsigned int*) ; 
 int regmap_write (struct i2c_client*,int,int) ; 

__attribute__((used)) static int mn88472_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct mn88472_config *pdata = client->dev.platform_data;
	struct mn88472_dev *dev;
	struct dtv_frontend_properties *c;
	int ret;
	unsigned int utmp;
	static const struct regmap_config regmap_config = {
		.reg_bits = 8,
		.val_bits = 8,
	};

	dev_dbg(&client->dev, "\n");

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev) {
		ret = -ENOMEM;
		goto err;
	}

	dev->i2c_write_max = pdata->i2c_wr_max ? pdata->i2c_wr_max : ~0;
	dev->clk = pdata->xtal;
	dev->ts_mode = pdata->ts_mode;
	dev->ts_clk = pdata->ts_clock;
	dev->client[0] = client;
	dev->regmap[0] = regmap_init_i2c(dev->client[0], &regmap_config);
	if (IS_ERR(dev->regmap[0])) {
		ret = PTR_ERR(dev->regmap[0]);
		goto err_kfree;
	}

	/*
	 * Chip has three I2C addresses for different register banks. Used
	 * addresses are 0x18, 0x1a and 0x1c. We register two dummy clients,
	 * 0x1a and 0x1c, in order to get own I2C client for each register bank.
	 *
	 * Also, register bank 2 do not support sequential I/O. Only single
	 * register write or read is allowed to that bank.
	 */
	dev->client[1] = i2c_new_dummy_device(client->adapter, 0x1a);
	if (IS_ERR(dev->client[1])) {
		ret = PTR_ERR(dev->client[1]);
		dev_err(&client->dev, "I2C registration failed\n");
		goto err_regmap_0_regmap_exit;
	}
	dev->regmap[1] = regmap_init_i2c(dev->client[1], &regmap_config);
	if (IS_ERR(dev->regmap[1])) {
		ret = PTR_ERR(dev->regmap[1]);
		goto err_client_1_i2c_unregister_device;
	}
	i2c_set_clientdata(dev->client[1], dev);

	dev->client[2] = i2c_new_dummy_device(client->adapter, 0x1c);
	if (IS_ERR(dev->client[2])) {
		ret = PTR_ERR(dev->client[2]);
		dev_err(&client->dev, "2nd I2C registration failed\n");
		goto err_regmap_1_regmap_exit;
	}
	dev->regmap[2] = regmap_init_i2c(dev->client[2], &regmap_config);
	if (IS_ERR(dev->regmap[2])) {
		ret = PTR_ERR(dev->regmap[2]);
		goto err_client_2_i2c_unregister_device;
	}
	i2c_set_clientdata(dev->client[2], dev);

	/* Check demod answers with correct chip id */
	ret = regmap_read(dev->regmap[2], 0xff, &utmp);
	if (ret)
		goto err_regmap_2_regmap_exit;

	dev_dbg(&client->dev, "chip id=%02x\n", utmp);

	if (utmp != 0x02) {
		ret = -ENODEV;
		goto err_regmap_2_regmap_exit;
	}

	/* Sleep because chip is active by default */
	ret = regmap_write(dev->regmap[2], 0x05, 0x3e);
	if (ret)
		goto err_regmap_2_regmap_exit;

	/* Create dvb frontend */
	memcpy(&dev->fe.ops, &mn88472_ops, sizeof(struct dvb_frontend_ops));
	dev->fe.demodulator_priv = client;
	*pdata->fe = &dev->fe;
	i2c_set_clientdata(client, dev);

	/* Init stats to indicate which stats are supported */
	c = &dev->fe.dtv_property_cache;
	c->strength.len = 1;
	c->cnr.len = 1;
	c->block_error.len = 1;
	c->block_count.len = 1;

	/* Setup callbacks */
	pdata->get_dvb_frontend = mn88472_get_dvb_frontend;

	dev_info(&client->dev, "Panasonic MN88472 successfully identified\n");

	return 0;
err_regmap_2_regmap_exit:
	regmap_exit(dev->regmap[2]);
err_client_2_i2c_unregister_device:
	i2c_unregister_device(dev->client[2]);
err_regmap_1_regmap_exit:
	regmap_exit(dev->regmap[1]);
err_client_1_i2c_unregister_device:
	i2c_unregister_device(dev->client[1]);
err_regmap_0_regmap_exit:
	regmap_exit(dev->regmap[0]);
err_kfree:
	kfree(dev);
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}