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
struct fusb302_chip {int dummy; } ;

/* Variables and functions */
 int fusb302_i2c_read (struct fusb302_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int fusb302_i2c_write (struct fusb302_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fusb302_i2c_mask_write(struct fusb302_chip *chip, u8 address,
				  u8 mask, u8 value)
{
	int ret = 0;
	u8 data;

	ret = fusb302_i2c_read(chip, address, &data);
	if (ret < 0)
		return ret;
	data &= ~mask;
	data |= value;
	ret = fusb302_i2c_write(chip, address, data);
	if (ret < 0)
		return ret;

	return ret;
}