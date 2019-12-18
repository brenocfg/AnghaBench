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
typedef  int u8 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  soft_rst_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int elants_i2c_send (struct i2c_client*,int const*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int elants_i2c_sw_reset(struct i2c_client *client)
{
	const u8 soft_rst_cmd[] = { 0x77, 0x77, 0x77, 0x77 };
	int error;

	error = elants_i2c_send(client, soft_rst_cmd,
				sizeof(soft_rst_cmd));
	if (error) {
		dev_err(&client->dev, "software reset failed: %d\n", error);
		return error;
	}

	/*
	 * We should wait at least 10 msec (but no more than 40) before
	 * sending fastboot or IAP command to the device.
	 */
	msleep(30);

	return 0;
}