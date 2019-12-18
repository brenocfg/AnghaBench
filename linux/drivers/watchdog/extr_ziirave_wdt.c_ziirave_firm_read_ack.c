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
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int ZIIRAVE_FIRM_DOWNLOAD_ACK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_read_byte (struct i2c_client*) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ziirave_firm_read_ack(struct watchdog_device *wdd)
{
	struct i2c_client *client = to_i2c_client(wdd->parent);
	int ret;

	ret = i2c_smbus_read_byte(client);
	if (ret < 0) {
		dev_err(&client->dev, "Failed to read status byte\n");
		return ret;
	}

	return ret == ZIIRAVE_FIRM_DOWNLOAD_ACK ? 0 : -EIO;
}