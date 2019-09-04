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
typedef  int u16 ;
struct w83795_data {int clkin; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  W83795_REG_CONFIG ; 
 int W83795_REG_CONFIG_START ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct w83795_data* i2c_get_clientdata (struct i2c_client*) ; 
 scalar_t__ reset ; 
 int w83795_read (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w83795_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void w83795_init_client(struct i2c_client *client)
{
	struct w83795_data *data = i2c_get_clientdata(client);
	static const u16 clkin[4] = {	/* in kHz */
		14318, 24000, 33333, 48000
	};
	u8 config;

	if (reset)
		w83795_write(client, W83795_REG_CONFIG, 0x80);

	/* Start monitoring if needed */
	config = w83795_read(client, W83795_REG_CONFIG);
	if (!(config & W83795_REG_CONFIG_START)) {
		dev_info(&client->dev, "Enabling monitoring operations\n");
		w83795_write(client, W83795_REG_CONFIG,
			     config | W83795_REG_CONFIG_START);
	}

	data->clkin = clkin[(config >> 3) & 0x3];
	dev_dbg(&client->dev, "clkin = %u kHz\n", data->clkin);
}