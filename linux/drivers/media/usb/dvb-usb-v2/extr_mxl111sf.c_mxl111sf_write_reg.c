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
struct mxl111sf_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MXL_CMD_REG_WRITE ; 
 int mxl111sf_ctrl_msg (struct mxl111sf_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ mxl_fail (int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mxl111sf_write_reg(struct mxl111sf_state *state, u8 addr, u8 data)
{
	u8 buf[] = { addr, data };
	int ret;

	pr_debug("W: (0x%02x, 0x%02x)\n", addr, data);

	ret = mxl111sf_ctrl_msg(state, MXL_CMD_REG_WRITE, buf, 2, NULL, 0);
	if (mxl_fail(ret))
		pr_err("error writing reg: 0x%02x, val: 0x%02x", addr, data);
	return ret;
}