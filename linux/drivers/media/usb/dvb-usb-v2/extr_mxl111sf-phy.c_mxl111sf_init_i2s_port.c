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
struct mxl111sf_reg_ctrl_info {int member_0; int member_1; int member_2; } ;

/* Variables and functions */
 int /*<<< orphan*/  V6_I2S_NUM_SAMPLES_REG ; 
 int mxl111sf_ctrl_program_regs (struct mxl111sf_state*,struct mxl111sf_reg_ctrl_info*) ; 
 int mxl111sf_write_reg (struct mxl111sf_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxl_debug (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ mxl_fail (int) ; 

int mxl111sf_init_i2s_port(struct mxl111sf_state *state, u8 sample_size)
{
	static struct mxl111sf_reg_ctrl_info init_i2s[] = {
		{0x1b, 0xff, 0x1e}, /* pin mux mode, Choose 656/I2S input */
		{0x15, 0x60, 0x60}, /* Enable I2S */
		{0x17, 0xe0, 0x20}, /* Input, MPEG MODE USB,
				       Inverted 656 Clock, I2S_SOFT_RESET,
				       0 : Normal operation, 1 : Reset State */
#if 0
		{0x12, 0x01, 0x00}, /* AUDIO_IRQ_CLR (Overflow Indicator) */
#endif
		{0x00, 0xff, 0x02}, /* Change to Control Page */
		{0x26, 0x0d, 0x0d}, /* I2S_MODE & BT656_SRC_SEL for FPGA only */
		{0x00, 0xff, 0x00},
		{0,    0,    0}
	};
	int ret;

	mxl_debug("(0x%02x)", sample_size);

	ret = mxl111sf_ctrl_program_regs(state, init_i2s);
	if (mxl_fail(ret))
		goto fail;

	ret = mxl111sf_write_reg(state, V6_I2S_NUM_SAMPLES_REG, sample_size);
	mxl_fail(ret);
fail:
	return ret;
}