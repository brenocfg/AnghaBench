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
 int mxl111sf_ctrl_msg (struct mxl111sf_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mxl_fail (int) ; 

__attribute__((used)) static int mxl111sf_i2c_get_data(struct mxl111sf_state *state,
				 u8 index, u8 *wdata, u8 *rdata)
{
	int ret = mxl111sf_ctrl_msg(state, wdata[0],
				    &wdata[1], 25, rdata, 24);
	mxl_fail(ret);

	return ret;
}