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
 int V8_SPI_MODE_REG ; 
 int mxl111sf_read_reg (struct mxl111sf_state*,int,int*) ; 
 int mxl111sf_write_reg (struct mxl111sf_state*,int,int) ; 
 int /*<<< orphan*/  mxl_debug (char*,int) ; 
 scalar_t__ mxl_fail (int) ; 

int mxl111sf_config_spi(struct mxl111sf_state *state, int onoff)
{
	u8 val;
	int ret;

	mxl_debug("(%d)", onoff);

	ret = mxl111sf_write_reg(state, 0x00, 0x02);
	if (mxl_fail(ret))
		goto fail;

	ret = mxl111sf_read_reg(state, V8_SPI_MODE_REG, &val);
	if (mxl_fail(ret))
		goto fail;

	if (onoff)
		val |= 0x04;
	else
		val &= ~0x04;

	ret = mxl111sf_write_reg(state, V8_SPI_MODE_REG, val);
	if (mxl_fail(ret))
		goto fail;

	ret = mxl111sf_write_reg(state, 0x00, 0x00);
	mxl_fail(ret);
fail:
	return ret;
}