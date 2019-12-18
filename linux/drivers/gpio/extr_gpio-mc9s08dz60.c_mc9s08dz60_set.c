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
struct mc9s08dz60 {int /*<<< orphan*/  client; } ;
typedef  int s32 ;

/* Variables and functions */
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int) ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mc9s_gpio_to_reg_and_bit (unsigned int,int*,int*) ; 

__attribute__((used)) static int mc9s08dz60_set(struct mc9s08dz60 *mc9s, unsigned offset, int val)
{
	u8 reg, bit;
	s32 value;

	mc9s_gpio_to_reg_and_bit(offset, &reg, &bit);
	value = i2c_smbus_read_byte_data(mc9s->client, reg);
	if (value >= 0) {
		if (val)
			value |= 1 << bit;
		else
			value &= ~(1 << bit);

		return i2c_smbus_write_byte_data(mc9s->client, reg, value);
	} else
		return value;

}