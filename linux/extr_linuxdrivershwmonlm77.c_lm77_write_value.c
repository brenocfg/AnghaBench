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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 scalar_t__ LM77_REG_CONF ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,scalar_t__,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_word_swapped (struct i2c_client*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lm77_write_value(struct i2c_client *client, u8 reg, u16 value)
{
	if (reg == LM77_REG_CONF)
		return i2c_smbus_write_byte_data(client, reg, value);
	else
		return i2c_smbus_write_word_swapped(client, reg, value);
}