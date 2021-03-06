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
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  RAYDIUM_WAIT_READY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int raydium_i2c_write_object (struct i2c_client*,int const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int raydium_i2c_disable_watch_dog(struct i2c_client *client)
{
	static const u8 cmd[] = { 0x0A, 0xAA };
	int error;

	error = raydium_i2c_write_object(client, cmd, sizeof(cmd),
					 RAYDIUM_WAIT_READY);
	if (error) {
		dev_err(&client->dev, "disable watchdog command failed: %d\n",
			error);
		return error;
	}

	return 0;
}