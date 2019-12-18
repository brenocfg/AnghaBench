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
struct tda18212_dev {struct i2c_client* client; int /*<<< orphan*/  regmap; int /*<<< orphan*/  cfg; } ;
struct tda18212_config {struct dvb_frontend* fe; } ;
struct regmap_config {int reg_bits; int val_bits; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_6__ {struct tda18212_config* platform_data; } ;
struct i2c_client {TYPE_2__ dev; } ;
struct dvb_tuner_ops {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  tuner_ops; int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;} ;
struct dvb_frontend {TYPE_1__ ops; struct tda18212_dev* tuner_priv; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,struct regmap_config const*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct tda18212_dev*) ; 
 int /*<<< orphan*/  kfree (struct tda18212_dev*) ; 
 struct tda18212_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct tda18212_config*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int) ; 
 struct tda18212_config tda18212_tuner_ops ; 

__attribute__((used)) static int tda18212_probe(struct i2c_client *client,
		const struct i2c_device_id *id)
{
	struct tda18212_config *cfg = client->dev.platform_data;
	struct dvb_frontend *fe = cfg->fe;
	struct tda18212_dev *dev;
	int ret;
	unsigned int chip_id;
	char *version;
	static const struct regmap_config regmap_config = {
		.reg_bits = 8,
		.val_bits = 8,
	};

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (dev == NULL) {
		ret = -ENOMEM;
		dev_err(&client->dev, "kzalloc() failed\n");
		goto err;
	}

	memcpy(&dev->cfg, cfg, sizeof(struct tda18212_config));
	dev->client = client;
	dev->regmap = devm_regmap_init_i2c(client, &regmap_config);
	if (IS_ERR(dev->regmap)) {
		ret = PTR_ERR(dev->regmap);
		goto err;
	}

	/* check if the tuner is there */
	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1); /* open I2C-gate */

	ret = regmap_read(dev->regmap, 0x00, &chip_id);
	dev_dbg(&dev->client->dev, "chip_id=%02x\n", chip_id);

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* close I2C-gate */

	if (ret)
		goto err;

	switch (chip_id) {
	case 0xc7:
		version = "M"; /* master */
		break;
	case 0x47:
		version = "S"; /* slave */
		break;
	default:
		ret = -ENODEV;
		goto err;
	}

	dev_info(&dev->client->dev,
			"NXP TDA18212HN/%s successfully identified\n", version);

	fe->tuner_priv = dev;
	memcpy(&fe->ops.tuner_ops, &tda18212_tuner_ops,
			sizeof(struct dvb_tuner_ops));
	i2c_set_clientdata(client, dev);

	return 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	kfree(dev);
	return ret;
}