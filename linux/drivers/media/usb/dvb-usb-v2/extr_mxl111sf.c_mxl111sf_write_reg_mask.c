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
 int mxl111sf_read_reg (struct mxl111sf_state*,int,int*) ; 
 int mxl111sf_write_reg (struct mxl111sf_state*,int,int) ; 
 scalar_t__ mxl_fail (int) ; 
 int /*<<< orphan*/  pr_err (char*,int,int,int) ; 

int mxl111sf_write_reg_mask(struct mxl111sf_state *state,
				   u8 addr, u8 mask, u8 data)
{
	int ret;
	u8 val = 0;

	if (mask != 0xff) {
		ret = mxl111sf_read_reg(state, addr, &val);
#if 1
		/* don't know why this usually errors out on the first try */
		if (mxl_fail(ret))
			pr_err("error writing addr: 0x%02x, mask: 0x%02x, data: 0x%02x, retrying...",
			       addr, mask, data);

		ret = mxl111sf_read_reg(state, addr, &val);
#endif
		if (mxl_fail(ret))
			goto fail;
	}
	val &= ~mask;
	val |= data;

	ret = mxl111sf_write_reg(state, addr, val);
	mxl_fail(ret);
fail:
	return ret;
}