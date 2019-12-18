#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct i2c_client* demodulator_priv; int /*<<< orphan*/  ops; } ;
struct si2168_dev {int chip_id; int version; int /*<<< orphan*/  spectral_inversion; int /*<<< orphan*/  ts_clock_gapped; int /*<<< orphan*/  ts_clock_inv; int /*<<< orphan*/  ts_mode; TYPE_1__ fe; TYPE_2__* muxc; int /*<<< orphan*/  firmware_name; int /*<<< orphan*/  i2c_mutex; } ;
struct si2168_config {int /*<<< orphan*/  spectral_inversion; int /*<<< orphan*/  ts_clock_gapped; int /*<<< orphan*/  ts_clock_inv; int /*<<< orphan*/  ts_mode; TYPE_1__** fe; int /*<<< orphan*/ * i2c_adapter; } ;
struct si2168_cmd {int* args; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_10__ {struct si2168_config* platform_data; } ;
struct i2c_client {TYPE_3__ dev; int /*<<< orphan*/  adapter; } ;
struct dvb_frontend_ops {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/ * adapter; struct i2c_client* priv; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_MUX_LOCKED ; 
 int /*<<< orphan*/  SI2168_A20_FIRMWARE ; 
 int /*<<< orphan*/  SI2168_A30_FIRMWARE ; 
 int /*<<< orphan*/  SI2168_B40_FIRMWARE ; 
#define  SI2168_CHIP_ID_A20 131 
#define  SI2168_CHIP_ID_A30 130 
#define  SI2168_CHIP_ID_B40 129 
#define  SI2168_CHIP_ID_D60 128 
 int /*<<< orphan*/  SI2168_D60_FIRMWARE ; 
 int /*<<< orphan*/  cmd_init (struct si2168_cmd*,char*,int,int) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_3__*,char*,int,int,int,...) ; 
 int /*<<< orphan*/  dev_warn (TYPE_3__*,char*,int) ; 
 int i2c_mux_add_adapter (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* i2c_mux_alloc (int /*<<< orphan*/ ,TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct si2168_dev*) ; 
 int /*<<< orphan*/  kfree (struct si2168_dev*) ; 
 struct si2168_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int si2168_cmd_execute (struct i2c_client*,struct si2168_cmd*) ; 
 int /*<<< orphan*/  si2168_deselect ; 
 int /*<<< orphan*/  si2168_ops ; 
 int /*<<< orphan*/  si2168_select ; 

__attribute__((used)) static int si2168_probe(struct i2c_client *client,
		const struct i2c_device_id *id)
{
	struct si2168_config *config = client->dev.platform_data;
	struct si2168_dev *dev;
	int ret;
	struct si2168_cmd cmd;

	dev_dbg(&client->dev, "\n");

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev) {
		ret = -ENOMEM;
		goto err;
	}

	i2c_set_clientdata(client, dev);
	mutex_init(&dev->i2c_mutex);

	/* Initialize */
	cmd_init(&cmd, "\xc0\x12\x00\x0c\x00\x0d\x16\x00\x00\x00\x00\x00\x00",
		 13, 0);
	ret = si2168_cmd_execute(client, &cmd);
	if (ret)
		goto err_kfree;

	/* Power up */
	cmd_init(&cmd, "\xc0\x06\x01\x0f\x00\x20\x20\x01", 8, 1);
	ret = si2168_cmd_execute(client, &cmd);
	if (ret)
		goto err_kfree;

	/* Query chip revision */
	cmd_init(&cmd, "\x02", 1, 13);
	ret = si2168_cmd_execute(client, &cmd);
	if (ret)
		goto err_kfree;

	dev->chip_id = cmd.args[1] << 24 | cmd.args[2] << 16 |
		       cmd.args[3] << 8 | cmd.args[4] << 0;

	switch (dev->chip_id) {
	case SI2168_CHIP_ID_A20:
		dev->firmware_name = SI2168_A20_FIRMWARE;
		break;
	case SI2168_CHIP_ID_A30:
		dev->firmware_name = SI2168_A30_FIRMWARE;
		break;
	case SI2168_CHIP_ID_B40:
		dev->firmware_name = SI2168_B40_FIRMWARE;
		break;
	case SI2168_CHIP_ID_D60:
		dev->firmware_name = SI2168_D60_FIRMWARE;
		break;
	default:
		dev_dbg(&client->dev, "unknown chip version Si21%d-%c%c%c\n",
			cmd.args[2], cmd.args[1], cmd.args[3], cmd.args[4]);
		ret = -ENODEV;
		goto err_kfree;
	}

	dev->version = (cmd.args[1]) << 24 | (cmd.args[3] - '0') << 16 |
		       (cmd.args[4] - '0') << 8 | (cmd.args[5]) << 0;

	/* create mux i2c adapter for tuner */
	dev->muxc = i2c_mux_alloc(client->adapter, &client->dev,
				  1, 0, I2C_MUX_LOCKED,
				  si2168_select, si2168_deselect);
	if (!dev->muxc) {
		ret = -ENOMEM;
		goto err_kfree;
	}
	dev->muxc->priv = client;
	ret = i2c_mux_add_adapter(dev->muxc, 0, 0, 0);
	if (ret)
		goto err_kfree;

	/* create dvb_frontend */
	memcpy(&dev->fe.ops, &si2168_ops, sizeof(struct dvb_frontend_ops));
	dev->fe.demodulator_priv = client;
	*config->i2c_adapter = dev->muxc->adapter[0];
	*config->fe = &dev->fe;
	dev->ts_mode = config->ts_mode;
	dev->ts_clock_inv = config->ts_clock_inv;
	dev->ts_clock_gapped = config->ts_clock_gapped;
	dev->spectral_inversion = config->spectral_inversion;

	dev_info(&client->dev, "Silicon Labs Si2168-%c%d%d successfully identified\n",
		 dev->version >> 24 & 0xff, dev->version >> 16 & 0xff,
		 dev->version >> 8 & 0xff);
	dev_info(&client->dev, "firmware version: %c %d.%d.%d\n",
		 dev->version >> 24 & 0xff, dev->version >> 16 & 0xff,
		 dev->version >> 8 & 0xff, dev->version >> 0 & 0xff);

	return 0;
err_kfree:
	kfree(dev);
err:
	dev_warn(&client->dev, "probe failed = %d\n", ret);
	return ret;
}