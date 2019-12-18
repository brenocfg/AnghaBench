#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct watchdog_device {int /*<<< orphan*/  parent; } ;
struct ihex_binrec {int /*<<< orphan*/  len; int /*<<< orphan*/ * data; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct firmware {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZIIRAVE_CMD_DOWNLOAD_END ; 
 int /*<<< orphan*/  ZIIRAVE_CMD_DOWNLOAD_START ; 
 int /*<<< orphan*/  ZIIRAVE_CMD_JUMP_TO_BOOTLOADER ; 
 int /*<<< orphan*/  ZIIRAVE_CMD_JUMP_TO_BOOTLOADER_MAGIC ; 
 int /*<<< orphan*/  ZIIRAVE_CMD_RESET_PROCESSOR ; 
 int /*<<< orphan*/  ZIIRAVE_CMD_RESET_PROCESSOR_MAGIC ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int i2c_smbus_write_byte (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ihex_binrec* ihex_next_binrec (struct ihex_binrec const*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 
 int ziirave_firm_read_ack (struct watchdog_device*) ; 
 int ziirave_firm_verify (struct watchdog_device*,struct firmware const*) ; 
 int ziirave_firm_write_pkt (struct watchdog_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ziirave_firm_upload(struct watchdog_device *wdd,
			       const struct firmware *fw)
{
	struct i2c_client *client = to_i2c_client(wdd->parent);
	const struct ihex_binrec *rec;
	int ret;

	ret = i2c_smbus_write_byte_data(client,
					ZIIRAVE_CMD_JUMP_TO_BOOTLOADER,
					ZIIRAVE_CMD_JUMP_TO_BOOTLOADER_MAGIC);
	if (ret) {
		dev_err(&client->dev, "Failed to jump to bootloader\n");
		return ret;
	}

	msleep(500);

	ret = i2c_smbus_write_byte(client, ZIIRAVE_CMD_DOWNLOAD_START);
	if (ret) {
		dev_err(&client->dev, "Failed to start download\n");
		return ret;
	}

	ret = ziirave_firm_read_ack(wdd);
	if (ret) {
		dev_err(&client->dev, "No ACK for start download\n");
		return ret;
	}

	msleep(500);

	for (rec = (void *)fw->data; rec; rec = ihex_next_binrec(rec)) {
		ret = ziirave_firm_write_pkt(wdd, be32_to_cpu(rec->addr),
					     rec->data, be16_to_cpu(rec->len));
		if (ret)
			return ret;
	}

	/*
	 * Finish firmware download process by sending a zero length
	 * payload
	 */
	ret = ziirave_firm_write_pkt(wdd, 0, NULL, 0);
	if (ret) {
		dev_err(&client->dev, "Failed to send EMPTY packet: %d\n", ret);
		return ret;
	}

	/* This sleep seems to be required */
	msleep(20);

	/* Start firmware verification */
	ret = ziirave_firm_verify(wdd, fw);
	if (ret) {
		dev_err(&client->dev,
			"Failed to verify firmware: %d\n", ret);
		return ret;
	}

	/* End download operation */
	ret = i2c_smbus_write_byte(client, ZIIRAVE_CMD_DOWNLOAD_END);
	if (ret) {
		dev_err(&client->dev,
			"Failed to end firmware download: %d\n", ret);
		return ret;
	}

	/* Reset the processor */
	ret = i2c_smbus_write_byte_data(client,
					ZIIRAVE_CMD_RESET_PROCESSOR,
					ZIIRAVE_CMD_RESET_PROCESSOR_MAGIC);
	if (ret) {
		dev_err(&client->dev,
			"Failed to reset the watchdog: %d\n", ret);
		return ret;
	}

	msleep(500);

	return 0;
}