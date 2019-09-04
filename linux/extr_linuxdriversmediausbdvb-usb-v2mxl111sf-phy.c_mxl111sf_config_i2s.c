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
 int /*<<< orphan*/  V6_I2S_STREAM_END_BIT_REG ; 
 int /*<<< orphan*/  V6_I2S_STREAM_START_BIT_REG ; 
 int mxl111sf_read_reg (struct mxl111sf_state*,int /*<<< orphan*/ ,int*) ; 
 int mxl111sf_write_reg (struct mxl111sf_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mxl_debug (char*,int,int) ; 
 scalar_t__ mxl_fail (int) ; 

int mxl111sf_config_i2s(struct mxl111sf_state *state,
			u8 msb_start_pos, u8 data_width)
{
	int ret;
	u8 tmp;

	mxl_debug("(0x%02x, 0x%02x)", msb_start_pos, data_width);

	ret = mxl111sf_read_reg(state, V6_I2S_STREAM_START_BIT_REG, &tmp);
	if (mxl_fail(ret))
		goto fail;

	tmp &= 0xe0;
	tmp |= msb_start_pos;
	ret = mxl111sf_write_reg(state, V6_I2S_STREAM_START_BIT_REG, tmp);
	if (mxl_fail(ret))
		goto fail;

	ret = mxl111sf_read_reg(state, V6_I2S_STREAM_END_BIT_REG, &tmp);
	if (mxl_fail(ret))
		goto fail;

	tmp &= 0xe0;
	tmp |= data_width;
	ret = mxl111sf_write_reg(state, V6_I2S_STREAM_END_BIT_REG, tmp);
	mxl_fail(ret);
fail:
	return ret;
}