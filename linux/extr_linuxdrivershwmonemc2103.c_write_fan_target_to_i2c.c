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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_FAN_TARGET_HI ; 
 int /*<<< orphan*/  REG_FAN_TARGET_LO ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void write_fan_target_to_i2c(struct i2c_client *client, u16 new_target)
{
	u8 high_byte = (new_target & 0x1fe0) >> 5;
	u8 low_byte = (new_target & 0x001f) << 3;
	i2c_smbus_write_byte_data(client, REG_FAN_TARGET_LO, low_byte);
	i2c_smbus_write_byte_data(client, REG_FAN_TARGET_HI, high_byte);
}