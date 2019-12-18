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
struct i2c_client {int /*<<< orphan*/  addr; int /*<<< orphan*/  adapter; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_adapter_id (int /*<<< orphan*/ ) ; 
 int read_byte (struct i2c_client*,int) ; 
 int /*<<< orphan*/  write_byte (struct i2c_client*,int,int) ; 

__attribute__((used)) static void asc7621_init_client(struct i2c_client *client)
{
	int value;

	/* Warn if part was not "READY" */

	value = read_byte(client, 0x40);

	if (value & 0x02) {
		dev_err(&client->dev,
			"Client (%d,0x%02x) config is locked.\n",
			i2c_adapter_id(client->adapter), client->addr);
	}
	if (!(value & 0x04)) {
		dev_err(&client->dev, "Client (%d,0x%02x) is not ready.\n",
			i2c_adapter_id(client->adapter), client->addr);
	}

/*
 * Start monitoring
 *
 * Try to clear LOCK, Set START, save everything else
 */
	value = (value & ~0x02) | 0x01;
	write_byte(client, 0x40, value & 0xff);

}