#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct regmap_config {int reg_bits; int val_bits; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_10__ {struct af9033_config* platform_data; } ;
struct i2c_client {TYPE_4__ dev; } ;
struct TYPE_9__ {int ts_mode; int clock; int tuner; } ;
struct TYPE_7__ {struct af9033_dev* demodulator_priv; TYPE_3__ ops; } ;
struct af9033_dev {int ts_mode_parallel; int ts_mode_serial; int is_it9135; int is_af9035; int /*<<< orphan*/  regmap; TYPE_1__ fe; TYPE_3__ cfg; struct i2c_client* client; } ;
struct af9033_config {int /*<<< orphan*/  regmap; TYPE_2__* ops; TYPE_1__** fe; } ;
struct TYPE_8__ {int /*<<< orphan*/  pid_filter_ctrl; int /*<<< orphan*/  pid_filter; } ;

/* Variables and functions */
#define  AF9033_TS_MODE_PARALLEL 136 
#define  AF9033_TS_MODE_SERIAL 135 
#define  AF9033_TS_MODE_USB 134 
#define  AF9033_TUNER_IT9135_38 133 
#define  AF9033_TUNER_IT9135_51 132 
#define  AF9033_TUNER_IT9135_52 131 
#define  AF9033_TUNER_IT9135_60 130 
#define  AF9033_TUNER_IT9135_61 129 
#define  AF9033_TUNER_IT9135_62 128 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct af9033_config af9033_ops ; 
 int /*<<< orphan*/  af9033_pid_filter ; 
 int /*<<< orphan*/  af9033_pid_filter_ctrl ; 
 int /*<<< orphan*/  dev_dbg (TYPE_4__*,char*,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,int) ; 
 int /*<<< orphan*/  dev_info (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct af9033_dev*) ; 
 int /*<<< orphan*/  kfree (struct af9033_dev*) ; 
 struct af9033_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,struct af9033_config*,int) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  regmap_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_init_i2c (struct i2c_client*,struct regmap_config const*) ; 
 int regmap_write (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int af9033_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct af9033_config *cfg = client->dev.platform_data;
	struct af9033_dev *dev;
	int ret;
	u8 buf[8];
	u32 reg;
	static const struct regmap_config regmap_config = {
		.reg_bits    =  24,
		.val_bits    =  8,
	};

	/* Allocate memory for the internal state */
	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev) {
		ret = -ENOMEM;
		goto err;
	}

	/* Setup the state */
	dev->client = client;
	memcpy(&dev->cfg, cfg, sizeof(dev->cfg));
	switch (dev->cfg.ts_mode) {
	case AF9033_TS_MODE_PARALLEL:
		dev->ts_mode_parallel = true;
		break;
	case AF9033_TS_MODE_SERIAL:
		dev->ts_mode_serial = true;
		break;
	case AF9033_TS_MODE_USB:
		/* USB mode for AF9035 */
	default:
		break;
	}

	if (dev->cfg.clock != 12000000) {
		ret = -ENODEV;
		dev_err(&client->dev,
			"Unsupported clock %u Hz. Only 12000000 Hz is supported currently\n",
			dev->cfg.clock);
		goto err_kfree;
	}

	/* Create regmap */
	dev->regmap = regmap_init_i2c(client, &regmap_config);
	if (IS_ERR(dev->regmap)) {
		ret = PTR_ERR(dev->regmap);
		goto err_kfree;
	}

	/* Firmware version */
	switch (dev->cfg.tuner) {
	case AF9033_TUNER_IT9135_38:
	case AF9033_TUNER_IT9135_51:
	case AF9033_TUNER_IT9135_52:
	case AF9033_TUNER_IT9135_60:
	case AF9033_TUNER_IT9135_61:
	case AF9033_TUNER_IT9135_62:
		dev->is_it9135 = true;
		reg = 0x004bfc;
		break;
	default:
		dev->is_af9035 = true;
		reg = 0x0083e9;
		break;
	}

	ret = regmap_bulk_read(dev->regmap, reg, &buf[0], 4);
	if (ret)
		goto err_regmap_exit;
	ret = regmap_bulk_read(dev->regmap, 0x804191, &buf[4], 4);
	if (ret)
		goto err_regmap_exit;

	dev_info(&client->dev,
		 "firmware version: LINK %d.%d.%d.%d - OFDM %d.%d.%d.%d\n",
		 buf[0], buf[1], buf[2], buf[3],
		 buf[4], buf[5], buf[6], buf[7]);

	/* Sleep as chip seems to be partly active by default */
	/* IT9135 did not like to sleep at that early */
	if (dev->is_af9035) {
		ret = regmap_write(dev->regmap, 0x80004c, 0x01);
		if (ret)
			goto err_regmap_exit;
		ret = regmap_write(dev->regmap, 0x800000, 0x00);
		if (ret)
			goto err_regmap_exit;
	}

	/* Create dvb frontend */
	memcpy(&dev->fe.ops, &af9033_ops, sizeof(dev->fe.ops));
	dev->fe.demodulator_priv = dev;
	*cfg->fe = &dev->fe;
	if (cfg->ops) {
		cfg->ops->pid_filter = af9033_pid_filter;
		cfg->ops->pid_filter_ctrl = af9033_pid_filter_ctrl;
	}
	cfg->regmap = dev->regmap;
	i2c_set_clientdata(client, dev);

	dev_info(&client->dev, "Afatech AF9033 successfully attached\n");

	return 0;
err_regmap_exit:
	regmap_exit(dev->regmap);
err_kfree:
	kfree(dev);
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}