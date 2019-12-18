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
typedef  int u32 ;
struct mlxreg_core_data {int mask; scalar_t__ bit; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int regmap_read (void*,int /*<<< orphan*/ ,int*) ; 
 int rol32 (int,scalar_t__) ; 
 int ror32 (int,scalar_t__) ; 

__attribute__((used)) static int
mlxreg_io_get_reg(void *regmap, struct mlxreg_core_data *data, u32 in_val,
		  bool rw_flag, u32 *regval)
{
	int ret;

	ret = regmap_read(regmap, data->reg, regval);
	if (ret)
		goto access_error;

	/*
	 * There are three kinds of attributes: single bit, full register's
	 * bits and bit sequence. For the first kind field mask indicates which
	 * bits are not related and field bit is set zero. For the second kind
	 * field mask is set to zero and field bit is set with all bits one.
	 * No special handling for such kind of attributes - pass value as is.
	 * For the third kind, field mask indicates which bits are related and
	 * field bit is set to the first bit number (from 1 to 32) is the bit
	 * sequence.
	 */
	if (!data->bit) {
		/* Single bit. */
		if (rw_flag) {
			/* For show: expose effective bit value as 0 or 1. */
			*regval = !!(*regval & ~data->mask);
		} else {
			/* For store: set effective bit value. */
			*regval &= data->mask;
			if (in_val)
				*regval |= ~data->mask;
		}
	} else if (data->mask) {
		/* Bit sequence. */
		if (rw_flag) {
			/* For show: mask and shift right. */
			*regval = ror32(*regval & data->mask, (data->bit - 1));
		} else {
			/* For store: shift to the position and mask. */
			in_val = rol32(in_val, data->bit - 1) & data->mask;
			/* Clear relevant bits and set them to new value. */
			*regval = (*regval & ~data->mask) | in_val;
		}
	}

access_error:
	return ret;
}