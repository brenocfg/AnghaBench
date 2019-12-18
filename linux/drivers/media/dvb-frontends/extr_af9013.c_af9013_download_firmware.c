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
typedef  int u8 ;
typedef  int u16 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct firmware {int size; int* data; } ;
struct af9013_state {int /*<<< orphan*/  regmap; struct i2c_client* client; } ;
struct TYPE_3__ {char const* name; } ;
struct TYPE_4__ {TYPE_1__ info; } ;

/* Variables and functions */
 char* AF9013_FIRMWARE ; 
 int ENODEV ; 
 scalar_t__ LEN_MAX ; 
 TYPE_2__ af9013_ops ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char const*,...) ; 
 int min (scalar_t__,int) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int,int*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 
 int regmap_read_poll_timeout (int /*<<< orphan*/ ,int,unsigned int,int,int,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int af9013_download_firmware(struct af9013_state *state)
{
	struct i2c_client *client = state->client;
	int ret, i, len, rem;
	unsigned int utmp;
	u8 buf[4];
	u16 checksum = 0;
	const struct firmware *firmware;
	const char *name = AF9013_FIRMWARE;

	dev_dbg(&client->dev, "\n");

	/* Check whether firmware is already running */
	ret = regmap_read(state->regmap, 0x98be, &utmp);
	if (ret)
		goto err;

	dev_dbg(&client->dev, "firmware status %02x\n", utmp);

	if (utmp == 0x0c)
		return 0;

	dev_info(&client->dev, "found a '%s' in cold state, will try to load a firmware\n",
		 af9013_ops.info.name);

	/* Request the firmware, will block and timeout */
	ret = request_firmware(&firmware, name, &client->dev);
	if (ret) {
		dev_info(&client->dev, "firmware file '%s' not found %d\n",
			 name, ret);
		goto err;
	}

	dev_info(&client->dev, "downloading firmware from file '%s'\n",
		 name);

	/* Write firmware checksum & size */
	for (i = 0; i < firmware->size; i++)
		checksum += firmware->data[i];

	buf[0] = (checksum >> 8) & 0xff;
	buf[1] = (checksum >> 0) & 0xff;
	buf[2] = (firmware->size >> 8) & 0xff;
	buf[3] = (firmware->size >> 0) & 0xff;
	ret = regmap_bulk_write(state->regmap, 0x50fc, buf, 4);
	if (ret)
		goto err_release_firmware;

	/* Download firmware */
	#define LEN_MAX 16
	for (rem = firmware->size; rem > 0; rem -= LEN_MAX) {
		len = min(LEN_MAX, rem);
		ret = regmap_bulk_write(state->regmap,
					0x5100 + firmware->size - rem,
					&firmware->data[firmware->size - rem],
					len);
		if (ret) {
			dev_err(&client->dev, "firmware download failed %d\n",
				ret);
			goto err_release_firmware;
		}
	}

	release_firmware(firmware);

	/* Boot firmware */
	ret = regmap_write(state->regmap, 0xe205, 0x01);
	if (ret)
		goto err;

	/* Check firmware status. 0c=OK, 04=fail */
	ret = regmap_read_poll_timeout(state->regmap, 0x98be, utmp,
				       (utmp == 0x0c || utmp == 0x04),
				       5000, 1000000);
	if (ret)
		goto err;

	dev_dbg(&client->dev, "firmware status %02x\n", utmp);

	if (utmp == 0x04) {
		ret = -ENODEV;
		dev_err(&client->dev, "firmware did not run\n");
		goto err;
	} else if (utmp != 0x0c) {
		ret = -ENODEV;
		dev_err(&client->dev, "firmware boot timeout\n");
		goto err;
	}

	dev_info(&client->dev, "found a '%s' in warm state\n",
		 af9013_ops.info.name);

	return 0;
err_release_firmware:
	release_firmware(firmware);
err:
	dev_dbg(&client->dev, "failed %d\n", ret);
	return ret;
}