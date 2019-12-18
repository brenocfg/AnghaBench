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
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int const,int) ; 
 int i2c_smbus_read_word_swapped (struct i2c_client*,int const) ; 
 int reg_page_map_set (struct i2c_client*,int const) ; 

__attribute__((used)) static int mt9m111_reg_read(struct i2c_client *client, const u16 reg)
{
	int ret;

	ret = reg_page_map_set(client, reg);
	if (!ret)
		ret = i2c_smbus_read_word_swapped(client, reg & 0xff);

	dev_dbg(&client->dev, "read  reg.%03x -> %04x\n", reg, ret);
	return ret;
}