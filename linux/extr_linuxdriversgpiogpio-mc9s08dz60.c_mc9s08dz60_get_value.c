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
struct gpio_chip {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 struct mc9s08dz60* gpiochip_get_data (struct gpio_chip*) ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mc9s_gpio_to_reg_and_bit (unsigned int,int*,int*) ; 

__attribute__((used)) static int mc9s08dz60_get_value(struct gpio_chip *gc, unsigned offset)
{
	u8 reg, bit;
	s32 value;
	struct mc9s08dz60 *mc9s = gpiochip_get_data(gc);

	mc9s_gpio_to_reg_and_bit(offset, &reg, &bit);
	value = i2c_smbus_read_byte_data(mc9s->client, reg);

	return (value >= 0) ? (value >> bit) & 0x1 : 0;
}