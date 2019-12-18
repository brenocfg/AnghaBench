#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int u8 ;
struct tda10071_reg_val_mask {int member_0; int member_1; int member_2; int /*<<< orphan*/  mask; int /*<<< orphan*/  val; int /*<<< orphan*/  reg; } ;
struct tda10071_dev {int pll_multiplier; int warm; int i2c_wr_max; int clk; int spec_inv; int tuner_i2c_addr; int ts_mode; int /*<<< orphan*/  regmap; struct i2c_client* client; } ;
struct tda10071_cmd {int* args; int len; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct firmware {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_20__ {int len; TYPE_8__* stat; } ;
struct TYPE_18__ {int len; TYPE_6__* stat; } ;
struct TYPE_16__ {int len; TYPE_4__* stat; } ;
struct TYPE_14__ {int len; TYPE_2__* stat; } ;
struct dtv_frontend_properties {TYPE_9__ block_error; TYPE_7__ post_bit_error; TYPE_5__ cnr; TYPE_3__ strength; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct tda10071_dev* demodulator_priv; } ;
struct TYPE_19__ {void* scale; } ;
struct TYPE_17__ {void* scale; } ;
struct TYPE_15__ {void* scale; } ;
struct TYPE_13__ {void* scale; } ;
struct TYPE_12__ {int* name; } ;
struct TYPE_11__ {TYPE_1__ info; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct tda10071_reg_val_mask*) ; 
 int CMD_BER_CONTROL ; 
 int CMD_DEMOD_INIT ; 
 int CMD_GET_FW_VERSION ; 
 int CMD_LNB_CONFIG ; 
 int CMD_MPEG_CONFIG ; 
 int CMD_SET_SLEEP_MODE ; 
 int CMD_TUNER_INIT ; 
 int EFAULT ; 
 void* FE_SCALE_NOT_AVAILABLE ; 
 int* TDA10071_FIRMWARE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int,int*,int) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int,int*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int,int,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,int*,int /*<<< orphan*/ *) ; 
 int tda10071_cmd_execute (struct tda10071_dev*,struct tda10071_cmd*) ; 
 TYPE_10__ tda10071_ops ; 
 int tda10071_wr_reg_mask (struct tda10071_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tda10071_init(struct dvb_frontend *fe)
{
	struct tda10071_dev *dev = fe->demodulator_priv;
	struct i2c_client *client = dev->client;
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	struct tda10071_cmd cmd;
	int ret, i, len, remaining, fw_size;
	unsigned int uitmp;
	const struct firmware *fw;
	u8 *fw_file = TDA10071_FIRMWARE;
	u8 tmp, buf[4];
	struct tda10071_reg_val_mask tab[] = {
		{ 0xcd, 0x00, 0x07 },
		{ 0x80, 0x00, 0x02 },
		{ 0xcd, 0x00, 0xc0 },
		{ 0xce, 0x00, 0x1b },
		{ 0x9d, 0x00, 0x01 },
		{ 0x9d, 0x00, 0x02 },
		{ 0x9e, 0x00, 0x01 },
		{ 0x87, 0x00, 0x80 },
		{ 0xce, 0x00, 0x08 },
		{ 0xce, 0x00, 0x10 },
	};
	struct tda10071_reg_val_mask tab2[] = {
		{ 0xf1, 0x70, 0xff },
		{ 0x88, dev->pll_multiplier, 0x3f },
		{ 0x89, 0x00, 0x10 },
		{ 0x89, 0x10, 0x10 },
		{ 0xc0, 0x01, 0x01 },
		{ 0xc0, 0x00, 0x01 },
		{ 0xe0, 0xff, 0xff },
		{ 0xe0, 0x00, 0xff },
		{ 0x96, 0x1e, 0x7e },
		{ 0x8b, 0x08, 0x08 },
		{ 0x8b, 0x00, 0x08 },
		{ 0x8f, 0x1a, 0x7e },
		{ 0x8c, 0x68, 0xff },
		{ 0x8d, 0x08, 0xff },
		{ 0x8e, 0x4c, 0xff },
		{ 0x8f, 0x01, 0x01 },
		{ 0x8b, 0x04, 0x04 },
		{ 0x8b, 0x00, 0x04 },
		{ 0x87, 0x05, 0x07 },
		{ 0x80, 0x00, 0x20 },
		{ 0xc8, 0x01, 0xff },
		{ 0xb4, 0x47, 0xff },
		{ 0xb5, 0x9c, 0xff },
		{ 0xb6, 0x7d, 0xff },
		{ 0xba, 0x00, 0x03 },
		{ 0xb7, 0x47, 0xff },
		{ 0xb8, 0x9c, 0xff },
		{ 0xb9, 0x7d, 0xff },
		{ 0xba, 0x00, 0x0c },
		{ 0xc8, 0x00, 0xff },
		{ 0xcd, 0x00, 0x04 },
		{ 0xcd, 0x00, 0x20 },
		{ 0xe8, 0x02, 0xff },
		{ 0xcf, 0x20, 0xff },
		{ 0x9b, 0xd7, 0xff },
		{ 0x9a, 0x01, 0x03 },
		{ 0xa8, 0x05, 0x0f },
		{ 0xa8, 0x65, 0xf0 },
		{ 0xa6, 0xa0, 0xf0 },
		{ 0x9d, 0x50, 0xfc },
		{ 0x9e, 0x20, 0xe0 },
		{ 0xa3, 0x1c, 0x7c },
		{ 0xd5, 0x03, 0x03 },
	};

	if (dev->warm) {
		/* warm state - wake up device from sleep */

		for (i = 0; i < ARRAY_SIZE(tab); i++) {
			ret = tda10071_wr_reg_mask(dev, tab[i].reg,
				tab[i].val, tab[i].mask);
			if (ret)
				goto error;
		}

		cmd.args[0] = CMD_SET_SLEEP_MODE;
		cmd.args[1] = 0;
		cmd.args[2] = 0;
		cmd.len = 3;
		ret = tda10071_cmd_execute(dev, &cmd);
		if (ret)
			goto error;
	} else {
		/* cold state - try to download firmware */

		/* request the firmware, this will block and timeout */
		ret = request_firmware(&fw, fw_file, &client->dev);
		if (ret) {
			dev_err(&client->dev,
				"did not find the firmware file '%s' (status %d). You can use <kernel_dir>/scripts/get_dvb_firmware to get the firmware\n",
				fw_file, ret);
			goto error;
		}

		/* init */
		for (i = 0; i < ARRAY_SIZE(tab2); i++) {
			ret = tda10071_wr_reg_mask(dev, tab2[i].reg,
				tab2[i].val, tab2[i].mask);
			if (ret)
				goto error_release_firmware;
		}

		/*  download firmware */
		ret = regmap_write(dev->regmap, 0xe0, 0x7f);
		if (ret)
			goto error_release_firmware;

		ret = regmap_write(dev->regmap, 0xf7, 0x81);
		if (ret)
			goto error_release_firmware;

		ret = regmap_write(dev->regmap, 0xf8, 0x00);
		if (ret)
			goto error_release_firmware;

		ret = regmap_write(dev->regmap, 0xf9, 0x00);
		if (ret)
			goto error_release_firmware;

		dev_info(&client->dev,
			 "found a '%s' in cold state, will try to load a firmware\n",
			 tda10071_ops.info.name);
		dev_info(&client->dev, "downloading firmware from file '%s'\n",
			 fw_file);

		/* do not download last byte */
		fw_size = fw->size - 1;

		for (remaining = fw_size; remaining > 0;
			remaining -= (dev->i2c_wr_max - 1)) {
			len = remaining;
			if (len > (dev->i2c_wr_max - 1))
				len = (dev->i2c_wr_max - 1);

			ret = regmap_bulk_write(dev->regmap, 0xfa,
				(u8 *) &fw->data[fw_size - remaining], len);
			if (ret) {
				dev_err(&client->dev,
					"firmware download failed=%d\n", ret);
				goto error_release_firmware;
			}
		}
		release_firmware(fw);

		ret = regmap_write(dev->regmap, 0xf7, 0x0c);
		if (ret)
			goto error;

		ret = regmap_write(dev->regmap, 0xe0, 0x00);
		if (ret)
			goto error;

		/* wait firmware start */
		msleep(250);

		/* firmware status */
		ret = regmap_read(dev->regmap, 0x51, &uitmp);
		if (ret)
			goto error;

		if (uitmp) {
			dev_info(&client->dev, "firmware did not run\n");
			ret = -EFAULT;
			goto error;
		} else {
			dev->warm = true;
		}

		cmd.args[0] = CMD_GET_FW_VERSION;
		cmd.len = 1;
		ret = tda10071_cmd_execute(dev, &cmd);
		if (ret)
			goto error;

		ret = regmap_bulk_read(dev->regmap, cmd.len, buf, 4);
		if (ret)
			goto error;

		dev_info(&client->dev, "firmware version %d.%d.%d.%d\n",
			 buf[0], buf[1], buf[2], buf[3]);
		dev_info(&client->dev, "found a '%s' in warm state\n",
			 tda10071_ops.info.name);

		ret = regmap_bulk_read(dev->regmap, 0x81, buf, 2);
		if (ret)
			goto error;

		cmd.args[0] = CMD_DEMOD_INIT;
		cmd.args[1] = ((dev->clk / 1000) >> 8) & 0xff;
		cmd.args[2] = ((dev->clk / 1000) >> 0) & 0xff;
		cmd.args[3] = buf[0];
		cmd.args[4] = buf[1];
		cmd.args[5] = dev->pll_multiplier;
		cmd.args[6] = dev->spec_inv;
		cmd.args[7] = 0x00;
		cmd.len = 8;
		ret = tda10071_cmd_execute(dev, &cmd);
		if (ret)
			goto error;

		if (dev->tuner_i2c_addr)
			tmp = dev->tuner_i2c_addr;
		else
			tmp = 0x14;

		cmd.args[0] = CMD_TUNER_INIT;
		cmd.args[1] = 0x00;
		cmd.args[2] = 0x00;
		cmd.args[3] = 0x00;
		cmd.args[4] = 0x00;
		cmd.args[5] = tmp;
		cmd.args[6] = 0x00;
		cmd.args[7] = 0x03;
		cmd.args[8] = 0x02;
		cmd.args[9] = 0x02;
		cmd.args[10] = 0x00;
		cmd.args[11] = 0x00;
		cmd.args[12] = 0x00;
		cmd.args[13] = 0x00;
		cmd.args[14] = 0x00;
		cmd.len = 15;
		ret = tda10071_cmd_execute(dev, &cmd);
		if (ret)
			goto error;

		cmd.args[0] = CMD_MPEG_CONFIG;
		cmd.args[1] = 0;
		cmd.args[2] = dev->ts_mode;
		cmd.args[3] = 0x00;
		cmd.args[4] = 0x04;
		cmd.args[5] = 0x00;
		cmd.len = 6;
		ret = tda10071_cmd_execute(dev, &cmd);
		if (ret)
			goto error;

		ret = regmap_update_bits(dev->regmap, 0xf0, 0x01, 0x01);
		if (ret)
			goto error;

		cmd.args[0] = CMD_LNB_CONFIG;
		cmd.args[1] = 0;
		cmd.args[2] = 150;
		cmd.args[3] = 3;
		cmd.args[4] = 22;
		cmd.args[5] = 1;
		cmd.args[6] = 1;
		cmd.args[7] = 30;
		cmd.args[8] = 30;
		cmd.args[9] = 30;
		cmd.args[10] = 30;
		cmd.len = 11;
		ret = tda10071_cmd_execute(dev, &cmd);
		if (ret)
			goto error;

		cmd.args[0] = CMD_BER_CONTROL;
		cmd.args[1] = 0;
		cmd.args[2] = 14;
		cmd.args[3] = 14;
		cmd.len = 4;
		ret = tda10071_cmd_execute(dev, &cmd);
		if (ret)
			goto error;
	}

	/* init stats here in order signal app which stats are supported */
	c->strength.len = 1;
	c->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->cnr.len = 1;
	c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_error.len = 1;
	c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->block_error.len = 1;
	c->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	return ret;
error_release_firmware:
	release_firmware(fw);
error:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}