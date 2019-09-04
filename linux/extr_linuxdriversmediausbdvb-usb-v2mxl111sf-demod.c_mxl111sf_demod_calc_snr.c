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
typedef  int /*<<< orphan*/  u16 ;
struct mxl111sf_demod_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALCULATE_SNR (int) ; 
 int /*<<< orphan*/  V6_SNR_RB_LSB_REG ; 
 int /*<<< orphan*/  V6_SNR_RB_MSB_REG ; 
 int mxl111sf_demod_read_reg (struct mxl111sf_demod_state*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ mxl_fail (int) ; 

__attribute__((used)) static int mxl111sf_demod_calc_snr(struct mxl111sf_demod_state *state,
				   u16 *snr)
{
	u8 val1, val2;
	int ret;

	*snr = 0;

	ret = mxl111sf_demod_read_reg(state, V6_SNR_RB_LSB_REG, &val1);
	if (mxl_fail(ret))
		goto fail;
	ret = mxl111sf_demod_read_reg(state, V6_SNR_RB_MSB_REG, &val2);
	if (mxl_fail(ret))
		goto fail;

	*snr = CALCULATE_SNR(val1 | ((val2 & 0x03) << 8));
fail:
	return ret;
}