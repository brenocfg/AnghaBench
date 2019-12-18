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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int i2c_smbus_read_i2c_block_data (struct i2c_client*,int,int,int*) ; 

__attribute__((used)) static int hp206c_read_20bit(struct i2c_client *client, u8 cmd)
{
	int ret;
	u8 values[3];

	ret = i2c_smbus_read_i2c_block_data(client, cmd, 3, values);
	if (ret < 0)
		return ret;
	if (ret != 3)
		return -EIO;
	return ((values[0] & 0xF) << 16) | (values[1] << 8) | (values[2]);
}