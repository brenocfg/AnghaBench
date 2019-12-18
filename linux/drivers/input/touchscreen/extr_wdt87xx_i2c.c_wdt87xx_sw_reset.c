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
 int /*<<< orphan*/  VND_CMD_RESET ; 
 int /*<<< orphan*/  WDT_FW_RESET_TIME ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int wdt87xx_send_command (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wdt87xx_sw_reset(struct i2c_client *client)
{
	int error;

	dev_dbg(&client->dev, "resetting device now\n");

	error = wdt87xx_send_command(client, VND_CMD_RESET, 0);
	if (error) {
		dev_err(&client->dev, "reset failed\n");
		return error;
	}

	/* Wait the device to be ready */
	msleep(WDT_FW_RESET_TIME);

	return 0;
}