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
struct apds990x_chip {struct i2c_client* client; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int APDS990x_CMD ; 
 int APDS990x_CMD_TYPE_MASK ; 
 int APDS990x_CMD_TYPE_RB ; 
 scalar_t__ i2c_smbus_write_byte_data (struct i2c_client*,int,int) ; 

__attribute__((used)) static int apds990x_write_byte(struct apds990x_chip *chip, u8 reg, u8 data)
{
	struct i2c_client *client = chip->client;
	s32 ret;

	reg &= ~APDS990x_CMD_TYPE_MASK;
	reg |= APDS990x_CMD | APDS990x_CMD_TYPE_RB;

	ret = i2c_smbus_write_byte_data(client, reg, data);
	return (int)ret;
}