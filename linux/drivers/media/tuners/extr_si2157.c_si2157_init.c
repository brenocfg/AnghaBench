#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct si2157_dev {int if_frequency; scalar_t__ chiptype; int active; int /*<<< orphan*/  stat_work; } ;
struct si2157_cmd {int* args; int wlen; int rlen; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct firmware {int size; int* data; } ;
struct TYPE_4__ {int len; TYPE_1__* stat; } ;
struct dtv_frontend_properties {TYPE_2__ strength; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct i2c_client* tuner_priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  scale; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FE_SCALE_NOT_AVAILABLE ; 
#define  SI2141_A10 134 
 char* SI2141_A10_FIRMWARE ; 
#define  SI2146_A10 133 
#define  SI2147_A30 132 
#define  SI2148_A20 131 
#define  SI2157_A30 130 
 char* SI2157_A30_FIRMWARE ; 
 int SI2157_ARGLEN ; 
 scalar_t__ SI2157_CHIPTYPE_SI2141 ; 
 scalar_t__ SI2157_CHIPTYPE_SI2146 ; 
#define  SI2158_A20 129 
 char* SI2158_A20_FIRMWARE ; 
#define  SI2177_A30 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 struct si2157_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  memcpy (int*,char*,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int si2157_cmd_execute (struct i2c_client*,struct si2157_cmd*) ; 

__attribute__((used)) static int si2157_init(struct dvb_frontend *fe)
{
	struct i2c_client *client = fe->tuner_priv;
	struct si2157_dev *dev = i2c_get_clientdata(client);
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	int ret, len, remaining;
	struct si2157_cmd cmd;
	const struct firmware *fw;
	const char *fw_name;
	unsigned int uitmp, chip_id;

	dev_dbg(&client->dev, "\n");

	/* Returned IF frequency is garbage when firmware is not running */
	memcpy(cmd.args, "\x15\x00\x06\x07", 4);
	cmd.wlen = 4;
	cmd.rlen = 4;
	ret = si2157_cmd_execute(client, &cmd);
	if (ret)
		goto err;

	uitmp = cmd.args[2] << 0 | cmd.args[3] << 8;
	dev_dbg(&client->dev, "if_frequency kHz=%u\n", uitmp);

	if (uitmp == dev->if_frequency / 1000)
		goto warm;

	/* power up */
	if (dev->chiptype == SI2157_CHIPTYPE_SI2146) {
		memcpy(cmd.args, "\xc0\x05\x01\x00\x00\x0b\x00\x00\x01", 9);
		cmd.wlen = 9;
	} else if (dev->chiptype == SI2157_CHIPTYPE_SI2141) {
		memcpy(cmd.args, "\xc0\x00\x0d\x0e\x00\x01\x01\x01\x01\x03", 10);
		cmd.wlen = 10;
	} else {
		memcpy(cmd.args, "\xc0\x00\x0c\x00\x00\x01\x01\x01\x01\x01\x01\x02\x00\x00\x01", 15);
		cmd.wlen = 15;
	}
	cmd.rlen = 1;
	ret = si2157_cmd_execute(client, &cmd);
	if (ret)
		goto err;

	/* Si2141 needs a second command before it answers the revision query */
	if (dev->chiptype == SI2157_CHIPTYPE_SI2141) {
		memcpy(cmd.args, "\xc0\x08\x01\x02\x00\x00\x01", 7);
		cmd.wlen = 7;
		ret = si2157_cmd_execute(client, &cmd);
		if (ret)
			goto err;
	}

	/* query chip revision */
	memcpy(cmd.args, "\x02", 1);
	cmd.wlen = 1;
	cmd.rlen = 13;
	ret = si2157_cmd_execute(client, &cmd);
	if (ret)
		goto err;

	chip_id = cmd.args[1] << 24 | cmd.args[2] << 16 | cmd.args[3] << 8 |
			cmd.args[4] << 0;

	#define SI2177_A30 ('A' << 24 | 77 << 16 | '3' << 8 | '0' << 0)
	#define SI2158_A20 ('A' << 24 | 58 << 16 | '2' << 8 | '0' << 0)
	#define SI2148_A20 ('A' << 24 | 48 << 16 | '2' << 8 | '0' << 0)
	#define SI2157_A30 ('A' << 24 | 57 << 16 | '3' << 8 | '0' << 0)
	#define SI2147_A30 ('A' << 24 | 47 << 16 | '3' << 8 | '0' << 0)
	#define SI2146_A10 ('A' << 24 | 46 << 16 | '1' << 8 | '0' << 0)
	#define SI2141_A10 ('A' << 24 | 41 << 16 | '1' << 8 | '0' << 0)

	switch (chip_id) {
	case SI2158_A20:
	case SI2148_A20:
		fw_name = SI2158_A20_FIRMWARE;
		break;
	case SI2141_A10:
		fw_name = SI2141_A10_FIRMWARE;
		break;
	case SI2177_A30:
		fw_name = SI2157_A30_FIRMWARE;
		break;
	case SI2157_A30:
	case SI2147_A30:
	case SI2146_A10:
		fw_name = NULL;
		break;
	default:
		dev_err(&client->dev, "unknown chip version Si21%d-%c%c%c\n",
				cmd.args[2], cmd.args[1],
				cmd.args[3], cmd.args[4]);
		ret = -EINVAL;
		goto err;
	}

	dev_info(&client->dev, "found a 'Silicon Labs Si21%d-%c%c%c'\n",
			cmd.args[2], cmd.args[1], cmd.args[3], cmd.args[4]);

	if (fw_name == NULL)
		goto skip_fw_download;

	/* request the firmware, this will block and timeout */
	ret = request_firmware(&fw, fw_name, &client->dev);
	if (ret) {
		dev_err(&client->dev, "firmware file '%s' not found\n",
				fw_name);
		goto err;
	}

	/* firmware should be n chunks of 17 bytes */
	if (fw->size % 17 != 0) {
		dev_err(&client->dev, "firmware file '%s' is invalid\n",
				fw_name);
		ret = -EINVAL;
		goto err_release_firmware;
	}

	dev_info(&client->dev, "downloading firmware from file '%s'\n",
			fw_name);

	for (remaining = fw->size; remaining > 0; remaining -= 17) {
		len = fw->data[fw->size - remaining];
		if (len > SI2157_ARGLEN) {
			dev_err(&client->dev, "Bad firmware length\n");
			ret = -EINVAL;
			goto err_release_firmware;
		}
		memcpy(cmd.args, &fw->data[(fw->size - remaining) + 1], len);
		cmd.wlen = len;
		cmd.rlen = 1;
		ret = si2157_cmd_execute(client, &cmd);
		if (ret) {
			dev_err(&client->dev, "firmware download failed %d\n",
					ret);
			goto err_release_firmware;
		}
	}

	release_firmware(fw);

skip_fw_download:
	/* reboot the tuner with new firmware? */
	memcpy(cmd.args, "\x01\x01", 2);
	cmd.wlen = 2;
	cmd.rlen = 1;
	ret = si2157_cmd_execute(client, &cmd);
	if (ret)
		goto err;

	/* query firmware version */
	memcpy(cmd.args, "\x11", 1);
	cmd.wlen = 1;
	cmd.rlen = 10;
	ret = si2157_cmd_execute(client, &cmd);
	if (ret)
		goto err;

	dev_info(&client->dev, "firmware version: %c.%c.%d\n",
			cmd.args[6], cmd.args[7], cmd.args[8]);
warm:
	/* init statistics in order signal app which are supported */
	c->strength.len = 1;
	c->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	/* start statistics polling */
	schedule_delayed_work(&dev->stat_work, msecs_to_jiffies(1000));

	dev->active = true;
	return 0;
err_release_firmware:
	release_firmware(fw);
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}