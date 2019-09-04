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
 int /*<<< orphan*/  mxl_debug (char*,int) ; 
 int /*<<< orphan*/  mxl_fail (int) ; 

__attribute__((used)) static int mxl111sf_get_gpi_state(struct mxl111sf_state *state, u8 pin, u8 *val)
{
	int ret;
	u8 tmp;

	mxl_debug("(0x%02x)", pin);

	*val = 0;

	switch (pin) {
	case 0:
	case 1:
	case 2:
	case 3:
		ret = mxl111sf_read_reg(state, 0x23, &tmp);
		if (mxl_fail(ret))
			goto fail;
		*val = (tmp >> (pin + 4)) & 0x01;
		break;
	case 4:
	case 5:
	case 6:
	case 7:
		ret = mxl111sf_read_reg(state, 0x2f, &tmp);
		if (mxl_fail(ret))
			goto fail;
		*val = (tmp >> pin) & 0x01;
		break;
	case 8:
	case 9:
	case 10:
		ret = mxl111sf_read_reg(state, 0x22, &tmp);
		if (mxl_fail(ret))
			goto fail;
		*val = (tmp >> (pin - 3)) & 0x01;
		break;
	default:
		return -EINVAL; /* invalid pin */
	}
fail:
	return ret;
}