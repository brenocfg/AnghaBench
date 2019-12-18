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
struct sx150x_pinctrl {struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int i2c_smbus_read_byte_data (struct i2c_client*,unsigned int) ; 
 unsigned int sx150x_maybe_swizzle (struct sx150x_pinctrl*,unsigned int,unsigned int) ; 
 int sx150x_regmap_reg_width (struct sx150x_pinctrl*,unsigned int) ; 

__attribute__((used)) static int sx150x_regmap_reg_read(void *context, unsigned int reg,
				  unsigned int *result)
{
	int ret, n;
	struct sx150x_pinctrl *pctl = context;
	struct i2c_client *i2c = pctl->client;
	const int width = sx150x_regmap_reg_width(pctl, reg);
	unsigned int idx, val;

	/*
	 * There are four potential cases covered by this function:
	 *
	 * 1) 8-pin chip, single configuration bit register
	 *
	 *	This is trivial the code below just needs to read:
	 *		reg  [ 7 6 5 4 3 2 1 0 ]
	 *
	 * 2) 8-pin chip, double configuration bit register (RegSense)
	 *
	 *	The read will be done as follows:
	 *		reg      [ 7 7 6 6 5 5 4 4 ]
	 *		reg + 1  [ 3 3 2 2 1 1 0 0 ]
	 *
	 * 3) 16-pin chip, single configuration bit register
	 *
	 *	The read will be done as follows:
	 *		reg     [ f e d c b a 9 8 ]
	 *		reg + 1 [ 7 6 5 4 3 2 1 0 ]
	 *
	 * 4) 16-pin chip, double configuration bit register (RegSense)
	 *
	 *	The read will be done as follows:
	 *		reg     [ f f e e d d c c ]
	 *		reg + 1 [ b b a a 9 9 8 8 ]
	 *		reg + 2 [ 7 7 6 6 5 5 4 4 ]
	 *		reg + 3 [ 3 3 2 2 1 1 0 0 ]
	 */

	for (n = width, val = 0, idx = reg; n > 0; n -= 8, idx++) {
		val <<= 8;

		ret = i2c_smbus_read_byte_data(i2c, idx);
		if (ret < 0)
			return ret;

		val |= ret;
	}

	*result = sx150x_maybe_swizzle(pctl, reg, val);

	return 0;
}