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
struct mxl111sf_state {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int mxl111sf_read_reg (struct mxl111sf_state*,int,int*) ; 
 int mxl111sf_write_reg (struct mxl111sf_state*,int,int) ; 
 int /*<<< orphan*/  mxl_debug_adv (char*,int,int) ; 
 scalar_t__ mxl_fail (int) ; 

__attribute__((used)) static int mxl111sf_set_gpo_state(struct mxl111sf_state *state, u8 pin, u8 val)
{
	int ret;
	u8 tmp;

	mxl_debug_adv("(%d, %d)", pin, val);

	if ((pin > 0) && (pin < 8)) {
		ret = mxl111sf_read_reg(state, 0x19, &tmp);
		if (mxl_fail(ret))
			goto fail;
		tmp &= ~(1 << (pin - 1));
		tmp |= (val << (pin - 1));
		ret = mxl111sf_write_reg(state, 0x19, tmp);
		if (mxl_fail(ret))
			goto fail;
	} else if (pin <= 10) {
		if (pin == 0)
			pin += 7;
		ret = mxl111sf_read_reg(state, 0x30, &tmp);
		if (mxl_fail(ret))
			goto fail;
		tmp &= ~(1 << (pin - 3));
		tmp |= (val << (pin - 3));
		ret = mxl111sf_write_reg(state, 0x30, tmp);
		if (mxl_fail(ret))
			goto fail;
	} else
		ret = -EINVAL;
fail:
	return ret;
}