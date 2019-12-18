#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct si2168_dev {int warm; int firmware_name; scalar_t__ chip_id; char version; int active; } ;
struct si2168_cmd {char* args; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct firmware {int size; int* data; } ;
struct TYPE_16__ {int len; TYPE_7__* stat; } ;
struct TYPE_14__ {int len; TYPE_5__* stat; } ;
struct TYPE_12__ {int len; TYPE_3__* stat; } ;
struct TYPE_10__ {int len; TYPE_1__* stat; } ;
struct dtv_frontend_properties {TYPE_8__ block_error; TYPE_6__ post_bit_count; TYPE_4__ post_bit_error; TYPE_2__ cnr; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct i2c_client* demodulator_priv; } ;
struct TYPE_15__ {void* scale; } ;
struct TYPE_13__ {void* scale; } ;
struct TYPE_11__ {void* scale; } ;
struct TYPE_9__ {void* scale; } ;

/* Variables and functions */
 int EINVAL ; 
 void* FE_SCALE_NOT_AVAILABLE ; 
 int SI2168_ARGLEN ; 
 int /*<<< orphan*/  SI2168_B40_FIRMWARE ; 
 int SI2168_B40_FIRMWARE_FALLBACK ; 
 scalar_t__ SI2168_CHIP_ID_B40 ; 
 int /*<<< orphan*/  cmd_init (struct si2168_cmd*,char*,int,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct si2168_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,int,int /*<<< orphan*/ *) ; 
 int si2168_cmd_execute (struct i2c_client*,struct si2168_cmd*) ; 
 int si2168_ts_bus_ctrl (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int si2168_init(struct dvb_frontend *fe)
{
	struct i2c_client *client = fe->demodulator_priv;
	struct si2168_dev *dev = i2c_get_clientdata(client);
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	int ret, len, remaining;
	const struct firmware *fw;
	struct si2168_cmd cmd;

	dev_dbg(&client->dev, "\n");

	/* initialize */
	cmd_init(&cmd, "\xc0\x12\x00\x0c\x00\x0d\x16\x00\x00\x00\x00\x00\x00",
		 13, 0);
	ret = si2168_cmd_execute(client, &cmd);
	if (ret)
		goto err;

	if (dev->warm) {
		/* resume */
		cmd_init(&cmd, "\xc0\x06\x08\x0f\x00\x20\x21\x01", 8, 1);
		ret = si2168_cmd_execute(client, &cmd);
		if (ret)
			goto err;

		udelay(100);
		cmd_init(&cmd, "\x85", 1, 1);
		ret = si2168_cmd_execute(client, &cmd);
		if (ret)
			goto err;

		goto warm;
	}

	/* power up */
	cmd_init(&cmd, "\xc0\x06\x01\x0f\x00\x20\x20\x01", 8, 1);
	ret = si2168_cmd_execute(client, &cmd);
	if (ret)
		goto err;

	/* request the firmware, this will block and timeout */
	ret = request_firmware(&fw, dev->firmware_name, &client->dev);
	if (ret) {
		/* fallback mechanism to handle old name for Si2168 B40 fw */
		if (dev->chip_id == SI2168_CHIP_ID_B40) {
			dev->firmware_name = SI2168_B40_FIRMWARE_FALLBACK;
			ret = request_firmware(&fw, dev->firmware_name,
					       &client->dev);
		}

		if (ret == 0) {
			dev_notice(&client->dev,
					"please install firmware file '%s'\n",
					SI2168_B40_FIRMWARE);
		} else {
			dev_err(&client->dev,
					"firmware file '%s' not found\n",
					dev->firmware_name);
			goto err_release_firmware;
		}
	}

	dev_info(&client->dev, "downloading firmware from file '%s'\n",
			dev->firmware_name);

	if ((fw->size % 17 == 0) && (fw->data[0] > 5)) {
		/* firmware is in the new format */
		for (remaining = fw->size; remaining > 0; remaining -= 17) {
			len = fw->data[fw->size - remaining];
			if (len > SI2168_ARGLEN) {
				ret = -EINVAL;
				break;
			}
			cmd_init(&cmd, &fw->data[(fw->size - remaining) + 1],
				 len, 1);
			ret = si2168_cmd_execute(client, &cmd);
			if (ret)
				break;
		}
	} else if (fw->size % 8 == 0) {
		/* firmware is in the old format */
		for (remaining = fw->size; remaining > 0; remaining -= 8) {
			cmd_init(&cmd, &fw->data[fw->size - remaining], 8, 1);
			ret = si2168_cmd_execute(client, &cmd);
			if (ret)
				break;
		}
	} else {
		/* bad or unknown firmware format */
		ret = -EINVAL;
	}

	if (ret) {
		dev_err(&client->dev, "firmware download failed %d\n", ret);
		goto err_release_firmware;
	}

	release_firmware(fw);

	cmd_init(&cmd, "\x01\x01", 2, 1);
	ret = si2168_cmd_execute(client, &cmd);
	if (ret)
		goto err;

	/* query firmware version */
	cmd_init(&cmd, "\x11", 1, 10);
	ret = si2168_cmd_execute(client, &cmd);
	if (ret)
		goto err;

	dev->version = (cmd.args[9] + '@') << 24 | (cmd.args[6] - '0') << 16 |
		       (cmd.args[7] - '0') << 8 | (cmd.args[8]) << 0;
	dev_info(&client->dev, "firmware version: %c %d.%d.%d\n",
		 dev->version >> 24 & 0xff, dev->version >> 16 & 0xff,
		 dev->version >> 8 & 0xff, dev->version >> 0 & 0xff);

	/* set ts mode */
	ret = si2168_ts_bus_ctrl(fe, 1);
	if (ret)
		goto err;

	dev->warm = true;
warm:
	/* Init stats here to indicate which stats are supported */
	c->cnr.len = 1;
	c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_error.len = 1;
	c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_count.len = 1;
	c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->block_error.len = 1;
	c->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	dev->active = true;

	return 0;
err_release_firmware:
	release_firmware(fw);
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}