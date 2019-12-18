#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct regmap_config {int reg_bits; int val_bits; } ;
struct m88rs6000t_reg_val {int member_0; int member_1; int reg; int val; } ;
struct m88rs6000t_dev {struct i2c_client* client; int /*<<< orphan*/  regmap; int /*<<< orphan*/  cfg; } ;
struct m88rs6000t_config {struct dvb_frontend* fe; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_6__ {struct m88rs6000t_config* platform_data; } ;
struct i2c_client {TYPE_2__ dev; } ;
struct dvb_tuner_ops {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  tuner_ops; } ;
struct dvb_frontend {TYPE_1__ ops; struct m88rs6000t_dev* tuner_priv; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct m88rs6000t_reg_val const*) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,struct regmap_config const*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct m88rs6000t_dev*) ; 
 int /*<<< orphan*/  kfree (struct m88rs6000t_dev*) ; 
 struct m88rs6000t_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct m88rs6000t_config m88rs6000t_tuner_ops ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct m88rs6000t_config*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int,int,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int m88rs6000t_probe(struct i2c_client *client,
		const struct i2c_device_id *id)
{
	struct m88rs6000t_config *cfg = client->dev.platform_data;
	struct dvb_frontend *fe = cfg->fe;
	struct m88rs6000t_dev *dev;
	int ret, i;
	unsigned int utmp;
	static const struct regmap_config regmap_config = {
		.reg_bits = 8,
		.val_bits = 8,
	};
	static const struct m88rs6000t_reg_val reg_vals[] = {
		{0x10, 0xfb},
		{0x24, 0x38},
		{0x11, 0x0a},
		{0x12, 0x00},
		{0x2b, 0x1c},
		{0x44, 0x48},
		{0x54, 0x24},
		{0x55, 0x06},
		{0x59, 0x00},
		{0x5b, 0x4c},
		{0x60, 0x8b},
		{0x61, 0xf4},
		{0x65, 0x07},
		{0x6d, 0x6f},
		{0x6e, 0x31},
		{0x3c, 0xf3},
		{0x37, 0x0f},
		{0x48, 0x28},
		{0x49, 0xd8},
		{0x70, 0x66},
		{0x71, 0xCF},
		{0x72, 0x81},
		{0x73, 0xA7},
		{0x74, 0x4F},
		{0x75, 0xFC},
	};

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev) {
		ret = -ENOMEM;
		dev_err(&client->dev, "kzalloc() failed\n");
		goto err;
	}

	memcpy(&dev->cfg, cfg, sizeof(struct m88rs6000t_config));
	dev->client = client;
	dev->regmap = devm_regmap_init_i2c(client, &regmap_config);
	if (IS_ERR(dev->regmap)) {
		ret = PTR_ERR(dev->regmap);
		goto err;
	}

	ret = regmap_update_bits(dev->regmap, 0x11, 0x08, 0x08);
	if (ret)
		goto err;
	usleep_range(5000, 50000);
	ret = regmap_update_bits(dev->regmap, 0x10, 0x01, 0x01);
	if (ret)
		goto err;
	usleep_range(10000, 50000);
	ret = regmap_write(dev->regmap, 0x07, 0x7d);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x04, 0x01);
	if (ret)
		goto err;

	/* check tuner chip id */
	ret = regmap_read(dev->regmap, 0x01, &utmp);
	if (ret)
		goto err;
	dev_info(&dev->client->dev, "chip_id=%02x\n", utmp);
	if (utmp != 0x64) {
		ret = -ENODEV;
		goto err;
	}

	/* tuner init. */
	ret = regmap_write(dev->regmap, 0x05, 0x40);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x11, 0x08);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x15, 0x6c);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x17, 0xc1);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x17, 0x81);
	if (ret)
		goto err;
	usleep_range(10000, 50000);
	ret = regmap_write(dev->regmap, 0x05, 0x00);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x11, 0x0a);
	if (ret)
		goto err;

	for (i = 0; i < ARRAY_SIZE(reg_vals); i++) {
		ret = regmap_write(dev->regmap,
				reg_vals[i].reg, reg_vals[i].val);
		if (ret)
			goto err;
	}

	dev_info(&dev->client->dev, "Montage M88RS6000 internal tuner successfully identified\n");

	fe->tuner_priv = dev;
	memcpy(&fe->ops.tuner_ops, &m88rs6000t_tuner_ops,
			sizeof(struct dvb_tuner_ops));
	i2c_set_clientdata(client, dev);
	return 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	kfree(dev);
	return ret;
}