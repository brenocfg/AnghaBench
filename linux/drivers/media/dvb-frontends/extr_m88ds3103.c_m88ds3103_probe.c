#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct m88ds3103_platform_data {int ts_clk; int clk_out; int /*<<< orphan*/  get_i2c_adapter; int /*<<< orphan*/  get_dvb_frontend; int /*<<< orphan*/  attach_in_use; int /*<<< orphan*/  lnb_en_pol; int /*<<< orphan*/  lnb_hv_pol; int /*<<< orphan*/  agc; int /*<<< orphan*/  envelope_mode; int /*<<< orphan*/  agc_inv; int /*<<< orphan*/  spec_inv; int /*<<< orphan*/  ts_clk_pol; int /*<<< orphan*/  ts_mode; int /*<<< orphan*/  i2c_wr_max; int /*<<< orphan*/  clk; } ;
struct TYPE_12__ {int /*<<< orphan*/  name; } ;
struct TYPE_14__ {int /*<<< orphan*/ * release; TYPE_2__ info; } ;
struct TYPE_13__ {struct m88ds3103_dev* demodulator_priv; TYPE_4__ ops; } ;
struct TYPE_17__ {int reg_bits; int val_bits; struct m88ds3103_dev* lock_arg; } ;
struct TYPE_11__ {int ts_clk; int clock_out; int /*<<< orphan*/  lnb_en_pol; int /*<<< orphan*/  lnb_hv_pol; int /*<<< orphan*/  agc; int /*<<< orphan*/  envelope_mode; int /*<<< orphan*/  agc_inv; int /*<<< orphan*/  spec_inv; int /*<<< orphan*/  ts_clk_pol; int /*<<< orphan*/  ts_mode; int /*<<< orphan*/  i2c_wr_max; int /*<<< orphan*/  clock; } ;
struct m88ds3103_dev {unsigned int chip_id; TYPE_3__ fe; TYPE_5__* muxc; int /*<<< orphan*/  regmap; TYPE_1__* cfg; TYPE_8__ regmap_config; TYPE_1__ config; struct i2c_client* client; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_16__ {struct m88ds3103_platform_data* platform_data; } ;
struct i2c_client {TYPE_6__ dev; int /*<<< orphan*/  adapter; } ;
struct dvb_frontend_ops {int dummy; } ;
struct TYPE_15__ {struct m88ds3103_dev* priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
#define  M88DS3103_CHIP_ID 132 
#define  M88DS3103_CLOCK_OUT_DISABLED 131 
#define  M88DS3103_CLOCK_OUT_ENABLED 130 
#define  M88DS3103_CLOCK_OUT_ENABLED_DIV2 129 
#define  M88RS6000_CHIP_ID 128 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_6__*,char*,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_6__*,char*,int) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,TYPE_8__*) ; 
 int i2c_mux_add_adapter (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* i2c_mux_alloc (int /*<<< orphan*/ ,TYPE_6__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct m88ds3103_dev*) ; 
 int /*<<< orphan*/  kfree (struct m88ds3103_dev*) ; 
 struct m88ds3103_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m88ds3103_get_dvb_frontend ; 
 int /*<<< orphan*/  m88ds3103_get_i2c_adapter ; 
 int /*<<< orphan*/  m88ds3103_ops ; 
 int /*<<< orphan*/  m88ds3103_select ; 
 int m88ds3103_update_bits (struct m88ds3103_dev*,int,int,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int m88ds3103_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct m88ds3103_dev *dev;
	struct m88ds3103_platform_data *pdata = client->dev.platform_data;
	int ret;
	unsigned int utmp;

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev) {
		ret = -ENOMEM;
		goto err;
	}

	dev->client = client;
	dev->config.clock = pdata->clk;
	dev->config.i2c_wr_max = pdata->i2c_wr_max;
	dev->config.ts_mode = pdata->ts_mode;
	dev->config.ts_clk = pdata->ts_clk * 1000;
	dev->config.ts_clk_pol = pdata->ts_clk_pol;
	dev->config.spec_inv = pdata->spec_inv;
	dev->config.agc_inv = pdata->agc_inv;
	dev->config.clock_out = pdata->clk_out;
	dev->config.envelope_mode = pdata->envelope_mode;
	dev->config.agc = pdata->agc;
	dev->config.lnb_hv_pol = pdata->lnb_hv_pol;
	dev->config.lnb_en_pol = pdata->lnb_en_pol;
	dev->cfg = &dev->config;
	/* create regmap */
	dev->regmap_config.reg_bits = 8,
	dev->regmap_config.val_bits = 8,
	dev->regmap_config.lock_arg = dev,
	dev->regmap = devm_regmap_init_i2c(client, &dev->regmap_config);
	if (IS_ERR(dev->regmap)) {
		ret = PTR_ERR(dev->regmap);
		goto err_kfree;
	}

	/* 0x00: chip id[6:0], 0x01: chip ver[7:0], 0x02: chip ver[15:8] */
	ret = regmap_read(dev->regmap, 0x00, &utmp);
	if (ret)
		goto err_kfree;

	dev->chip_id = utmp >> 1;
	dev_dbg(&client->dev, "chip_id=%02x\n", dev->chip_id);

	switch (dev->chip_id) {
	case M88RS6000_CHIP_ID:
	case M88DS3103_CHIP_ID:
		break;
	default:
		ret = -ENODEV;
		dev_err(&client->dev, "Unknown device. Chip_id=%02x\n", dev->chip_id);
		goto err_kfree;
	}

	switch (dev->cfg->clock_out) {
	case M88DS3103_CLOCK_OUT_DISABLED:
		utmp = 0x80;
		break;
	case M88DS3103_CLOCK_OUT_ENABLED:
		utmp = 0x00;
		break;
	case M88DS3103_CLOCK_OUT_ENABLED_DIV2:
		utmp = 0x10;
		break;
	default:
		ret = -EINVAL;
		goto err_kfree;
	}

	if (!pdata->ts_clk) {
		ret = -EINVAL;
		goto err_kfree;
	}

	/* 0x29 register is defined differently for m88rs6000. */
	/* set internal tuner address to 0x21 */
	if (dev->chip_id == M88RS6000_CHIP_ID)
		utmp = 0x00;

	ret = regmap_write(dev->regmap, 0x29, utmp);
	if (ret)
		goto err_kfree;

	/* sleep */
	ret = m88ds3103_update_bits(dev, 0x08, 0x01, 0x00);
	if (ret)
		goto err_kfree;
	ret = m88ds3103_update_bits(dev, 0x04, 0x01, 0x01);
	if (ret)
		goto err_kfree;
	ret = m88ds3103_update_bits(dev, 0x23, 0x10, 0x10);
	if (ret)
		goto err_kfree;

	/* create mux i2c adapter for tuner */
	dev->muxc = i2c_mux_alloc(client->adapter, &client->dev, 1, 0, 0,
				  m88ds3103_select, NULL);
	if (!dev->muxc) {
		ret = -ENOMEM;
		goto err_kfree;
	}
	dev->muxc->priv = dev;
	ret = i2c_mux_add_adapter(dev->muxc, 0, 0, 0);
	if (ret)
		goto err_kfree;

	/* create dvb_frontend */
	memcpy(&dev->fe.ops, &m88ds3103_ops, sizeof(struct dvb_frontend_ops));
	if (dev->chip_id == M88RS6000_CHIP_ID)
		strscpy(dev->fe.ops.info.name, "Montage Technology M88RS6000",
			sizeof(dev->fe.ops.info.name));
	if (!pdata->attach_in_use)
		dev->fe.ops.release = NULL;
	dev->fe.demodulator_priv = dev;
	i2c_set_clientdata(client, dev);

	/* setup callbacks */
	pdata->get_dvb_frontend = m88ds3103_get_dvb_frontend;
	pdata->get_i2c_adapter = m88ds3103_get_i2c_adapter;
	return 0;
err_kfree:
	kfree(dev);
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}