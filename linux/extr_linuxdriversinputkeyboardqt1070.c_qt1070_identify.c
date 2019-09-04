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
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHIP_ID ; 
 int /*<<< orphan*/  FW_VERSION ; 
 int QT1070_CHIP_ID ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int qt1070_read (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool qt1070_identify(struct i2c_client *client)
{
	int id, ver;

	/* Read Chip ID */
	id = qt1070_read(client, CHIP_ID);
	if (id != QT1070_CHIP_ID) {
		dev_err(&client->dev, "ID %d not supported\n", id);
		return false;
	}

	/* Read firmware version */
	ver = qt1070_read(client, FW_VERSION);
	if (ver < 0) {
		dev_err(&client->dev, "could not read the firmware version\n");
		return false;
	}

	dev_info(&client->dev, "AT42QT1070 firmware version %x\n", ver);

	return true;
}