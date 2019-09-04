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
struct tsl2563_chip {struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int TSL2563_CMD ; 
 int TSL2563_REG_ID ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int) ; 

__attribute__((used)) static int tsl2563_read_id(struct tsl2563_chip *chip, u8 *id)
{
	struct i2c_client *client = chip->client;
	int ret;

	ret = i2c_smbus_read_byte_data(client, TSL2563_CMD | TSL2563_REG_ID);
	if (ret < 0)
		return ret;

	*id = ret;

	return 0;
}