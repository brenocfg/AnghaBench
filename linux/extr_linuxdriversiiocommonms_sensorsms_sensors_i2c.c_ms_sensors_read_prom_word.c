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
typedef  int u16 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_read_word_swapped (struct i2c_client*,int) ; 

int ms_sensors_read_prom_word(void *cli, int cmd, u16 *word)
{
	int ret;
	struct i2c_client *client = cli;

	ret = i2c_smbus_read_word_swapped(client, cmd);
	if (ret < 0) {
		dev_err(&client->dev, "Failed to read prom word\n");
		return ret;
	}
	*word = ret;

	return 0;
}