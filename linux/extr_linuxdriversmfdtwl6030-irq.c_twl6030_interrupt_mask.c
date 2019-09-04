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

/* Variables and functions */
 scalar_t__ REG_INT_STS_A ; 
 int /*<<< orphan*/  TWL_MODULE_PIH ; 
 int twl_i2c_read_u8 (int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 
 int twl_i2c_write_u8 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

int twl6030_interrupt_mask(u8 bit_mask, u8 offset)
{
	int ret;
	u8 mask_value;

	ret = twl_i2c_read_u8(TWL_MODULE_PIH, &mask_value,
			REG_INT_STS_A + offset);
	mask_value |= (bit_mask);
	ret |= twl_i2c_write_u8(TWL_MODULE_PIH, mask_value,
			REG_INT_STS_A + offset); /* mask INT_MSK_A/B/C */
	return ret;
}