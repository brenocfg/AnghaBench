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
struct i2c_client {int /*<<< orphan*/  addr; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  boot_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int elants_i2c_send (struct i2c_client*,int const*,int) ; 

__attribute__((used)) static int elants_i2c_fastboot(struct i2c_client *client)
{
	const u8 boot_cmd[] = { 0x4D, 0x61, 0x69, 0x6E };
	int error;

	error = elants_i2c_send(client, boot_cmd, sizeof(boot_cmd));
	if (error) {
		dev_err(&client->dev, "boot failed: %d\n", error);
		return error;
	}

	dev_dbg(&client->dev, "boot success -- 0x%x\n", client->addr);
	return 0;
}