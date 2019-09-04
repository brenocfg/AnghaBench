#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct m88ds3103_dev {int warm; scalar_t__ chip_id; int /*<<< orphan*/  regmap; TYPE_1__* cfg; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct firmware {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_17__ {int len; TYPE_7__* stat; } ;
struct TYPE_15__ {int len; TYPE_5__* stat; } ;
struct TYPE_13__ {int len; TYPE_3__* stat; } ;
struct dtv_frontend_properties {TYPE_8__ post_bit_count; TYPE_6__ post_bit_error; TYPE_4__ cnr; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct m88ds3103_dev* demodulator_priv; } ;
struct TYPE_11__ {int /*<<< orphan*/  name; } ;
struct TYPE_18__ {TYPE_2__ info; } ;
struct TYPE_16__ {void* scale; } ;
struct TYPE_14__ {void* scale; } ;
struct TYPE_12__ {void* scale; } ;
struct TYPE_10__ {int i2c_wr_max; } ;

/* Variables and functions */
 int EINVAL ; 
 void* FE_SCALE_NOT_AVAILABLE ; 
 char* M88DS3103_FIRMWARE ; 
 scalar_t__ M88RS6000_CHIP_ID ; 
 char* M88RS6000_FIRMWARE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_9__ m88ds3103_ops ; 
 int m88ds3103_update_bits (struct m88ds3103_dev*,int,int,int) ; 
 int min (int,int) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int m88ds3103_init(struct dvb_frontend *fe)
{
	struct m88ds3103_dev *dev = fe->demodulator_priv;
	struct i2c_client *client = dev->client;
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	int ret, len, rem;
	unsigned int utmp;
	const struct firmware *firmware;
	const char *name;

	dev_dbg(&client->dev, "\n");

	/* set cold state by default */
	dev->warm = false;

	/* wake up device from sleep */
	ret = m88ds3103_update_bits(dev, 0x08, 0x01, 0x01);
	if (ret)
		goto err;
	ret = m88ds3103_update_bits(dev, 0x04, 0x01, 0x00);
	if (ret)
		goto err;
	ret = m88ds3103_update_bits(dev, 0x23, 0x10, 0x00);
	if (ret)
		goto err;

	/* firmware status */
	ret = regmap_read(dev->regmap, 0xb9, &utmp);
	if (ret)
		goto err;

	dev_dbg(&client->dev, "firmware=%02x\n", utmp);

	if (utmp)
		goto warm;

	/* global reset, global diseqc reset, golbal fec reset */
	ret = regmap_write(dev->regmap, 0x07, 0xe0);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap, 0x07, 0x00);
	if (ret)
		goto err;

	/* cold state - try to download firmware */
	dev_info(&client->dev, "found a '%s' in cold state\n",
		 m88ds3103_ops.info.name);

	if (dev->chip_id == M88RS6000_CHIP_ID)
		name = M88RS6000_FIRMWARE;
	else
		name = M88DS3103_FIRMWARE;
	/* request the firmware, this will block and timeout */
	ret = request_firmware(&firmware, name, &client->dev);
	if (ret) {
		dev_err(&client->dev, "firmware file '%s' not found\n", name);
		goto err;
	}

	dev_info(&client->dev, "downloading firmware from file '%s'\n", name);

	ret = regmap_write(dev->regmap, 0xb2, 0x01);
	if (ret)
		goto err_release_firmware;

	for (rem = firmware->size; rem > 0; rem -= (dev->cfg->i2c_wr_max - 1)) {
		len = min(dev->cfg->i2c_wr_max - 1, rem);
		ret = regmap_bulk_write(dev->regmap, 0xb0,
					&firmware->data[firmware->size - rem],
					len);
		if (ret) {
			dev_err(&client->dev, "firmware download failed %d\n",
				ret);
			goto err_release_firmware;
		}
	}

	ret = regmap_write(dev->regmap, 0xb2, 0x00);
	if (ret)
		goto err_release_firmware;

	release_firmware(firmware);

	ret = regmap_read(dev->regmap, 0xb9, &utmp);
	if (ret)
		goto err;

	if (!utmp) {
		ret = -EINVAL;
		dev_info(&client->dev, "firmware did not run\n");
		goto err;
	}

	dev_info(&client->dev, "found a '%s' in warm state\n",
		 m88ds3103_ops.info.name);
	dev_info(&client->dev, "firmware version: %X.%X\n",
		 (utmp >> 4) & 0xf, (utmp >> 0 & 0xf));

warm:
	/* warm state */
	dev->warm = true;

	/* init stats here in order signal app which stats are supported */
	c->cnr.len = 1;
	c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_error.len = 1;
	c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_count.len = 1;
	c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	return 0;
err_release_firmware:
	release_firmware(firmware);
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}