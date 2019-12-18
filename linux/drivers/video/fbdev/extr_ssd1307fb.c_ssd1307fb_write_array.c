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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct ssd1307fb_array {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_master_send (struct i2c_client*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ssd1307fb_write_array(struct i2c_client *client,
				 struct ssd1307fb_array *array, u32 len)
{
	int ret;

	len += sizeof(struct ssd1307fb_array);

	ret = i2c_master_send(client, (u8 *)array, len);
	if (ret != len) {
		dev_err(&client->dev, "Couldn't send I2C command.\n");
		return ret;
	}

	return 0;
}