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
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int) ; 

__attribute__((used)) static inline u8 read_byte(struct i2c_client *client, u8 reg)
{
	int res = i2c_smbus_read_byte_data(client, reg);
	if (res < 0) {
		dev_err(&client->dev,
			"Unable to read from register 0x%02x.\n", reg);
		return 0;
	}
	return res & 0xff;
}