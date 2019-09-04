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
 int i2c_smbus_read_byte_data (struct i2c_client*,int const) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int const,int) ; 

__attribute__((used)) static int ml86v7667_mask_set(struct i2c_client *client, const u8 reg,
			      const u8 mask, const u8 data)
{
	int val = i2c_smbus_read_byte_data(client, reg);
	if (val < 0)
		return val;

	val = (val & ~mask) | (data & mask);
	return i2c_smbus_write_byte_data(client, reg, val);
}