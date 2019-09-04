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
struct mxl111sf_state {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MXL_CMD_REG_READ ; 
 int mxl111sf_ctrl_msg (struct mxl111sf_state*,int /*<<< orphan*/ ,scalar_t__*,int,scalar_t__*,int) ; 
 int /*<<< orphan*/  mxl_debug (char*,scalar_t__) ; 
 scalar_t__ mxl_fail (int) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__,scalar_t__,scalar_t__) ; 

int mxl111sf_read_reg(struct mxl111sf_state *state, u8 addr, u8 *data)
{
	u8 buf[2];
	int ret;

	ret = mxl111sf_ctrl_msg(state, MXL_CMD_REG_READ, &addr, 1, buf, 2);
	if (mxl_fail(ret)) {
		mxl_debug("error reading reg: 0x%02x", addr);
		goto fail;
	}

	if (buf[0] == addr)
		*data = buf[1];
	else {
		pr_err("invalid response reading reg: 0x%02x != 0x%02x, 0x%02x",
		    addr, buf[0], buf[1]);
		ret = -EINVAL;
	}

	pr_debug("R: (0x%02x, 0x%02x)\n", addr, buf[1]);
fail:
	return ret;
}