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

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,char*,int) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u8 emc6w201_read8(struct i2c_client *client, u8 reg)
{
	int val;

	val = i2c_smbus_read_byte_data(client, reg);
	if (unlikely(val < 0)) {
		dev_err(&client->dev, "%d-bit %s failed at 0x%02x\n",
			8, "read", reg);
		return 0x00;	/* Arbitrary value */
	}

	return val;
}