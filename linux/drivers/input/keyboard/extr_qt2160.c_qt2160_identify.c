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
 int /*<<< orphan*/  QT2160_CMD_CHIPID ; 
 int /*<<< orphan*/  QT2160_CMD_CODEVER ; 
 int /*<<< orphan*/  QT2160_CMD_SUBVER ; 
 int QT2160_VALID_CHIPID ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int,int) ; 
 int qt2160_read (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool qt2160_identify(struct i2c_client *client)
{
	int id, ver, rev;

	/* Read Chid ID to check if chip is valid */
	id = qt2160_read(client, QT2160_CMD_CHIPID);
	if (id != QT2160_VALID_CHIPID) {
		dev_err(&client->dev, "ID %d not supported\n", id);
		return false;
	}

	/* Read chip firmware version */
	ver = qt2160_read(client, QT2160_CMD_CODEVER);
	if (ver < 0) {
		dev_err(&client->dev, "could not get firmware version\n");
		return false;
	}

	/* Read chip firmware revision */
	rev = qt2160_read(client, QT2160_CMD_SUBVER);
	if (rev < 0) {
		dev_err(&client->dev, "could not get firmware revision\n");
		return false;
	}

	dev_info(&client->dev, "AT42QT2160 firmware version %d.%d.%d\n",
			ver >> 4, ver & 0xf, rev);

	return true;
}