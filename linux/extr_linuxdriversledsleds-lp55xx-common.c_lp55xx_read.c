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
struct lp55xx_chip {int /*<<< orphan*/  cl; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ i2c_smbus_read_byte_data (int /*<<< orphan*/ ,scalar_t__) ; 

int lp55xx_read(struct lp55xx_chip *chip, u8 reg, u8 *val)
{
	s32 ret;

	ret = i2c_smbus_read_byte_data(chip->cl, reg);
	if (ret < 0)
		return ret;

	*val = ret;
	return 0;
}