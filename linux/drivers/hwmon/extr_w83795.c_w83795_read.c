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
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int) ; 
 int w83795_set_bank (struct i2c_client*,int) ; 

__attribute__((used)) static u8 w83795_read(struct i2c_client *client, u16 reg)
{
	int err;

	err = w83795_set_bank(client, reg >> 8);
	if (err < 0)
		return 0x00;	/* Arbitrary */

	err = i2c_smbus_read_byte_data(client, reg & 0xff);
	if (err < 0) {
		dev_err(&client->dev,
			"Failed to read from register 0x%03x, err %d\n",
			(int)reg, err);
		return 0x00;	/* Arbitrary */
	}
	return err;
}