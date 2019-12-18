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
typedef  int u16 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int,int /*<<< orphan*/ ) ; 
 int w83795_set_bank (struct i2c_client*,int) ; 

__attribute__((used)) static int w83795_write(struct i2c_client *client, u16 reg, u8 value)
{
	int err;

	err = w83795_set_bank(client, reg >> 8);
	if (err < 0)
		return err;

	err = i2c_smbus_write_byte_data(client, reg & 0xff, value);
	if (err < 0)
		dev_err(&client->dev,
			"Failed to write to register 0x%03x, err %d\n",
			(int)reg, err);
	return err;
}