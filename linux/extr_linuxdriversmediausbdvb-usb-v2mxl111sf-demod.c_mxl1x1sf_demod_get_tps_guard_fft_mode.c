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
struct mxl111sf_demod_state {int dummy; } ;
typedef  enum fe_transmit_mode { ____Placeholder_fe_transmit_mode } fe_transmit_mode ;

/* Variables and functions */
 int TRANSMISSION_MODE_2K ; 
 int TRANSMISSION_MODE_4K ; 
 int TRANSMISSION_MODE_8K ; 
 int /*<<< orphan*/  V6_MODE_TPS_REG ; 
 int V6_PARAM_FFT_MODE_MASK ; 
 int mxl111sf_demod_read_reg (struct mxl111sf_demod_state*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ mxl_fail (int) ; 

__attribute__((used)) static
int mxl1x1sf_demod_get_tps_guard_fft_mode(struct mxl111sf_demod_state *state,
					  enum fe_transmit_mode *fft_mode)
{
	u8 val;
	int ret = mxl111sf_demod_read_reg(state, V6_MODE_TPS_REG, &val);
	/* FFT Mode, 00:2K, 01:8K, 10:4K */
	if (mxl_fail(ret))
		goto fail;

	switch ((val & V6_PARAM_FFT_MODE_MASK) >> 2) {
	case 0:
		*fft_mode = TRANSMISSION_MODE_2K;
		break;
	case 1:
		*fft_mode = TRANSMISSION_MODE_8K;
		break;
	case 2:
		*fft_mode = TRANSMISSION_MODE_4K;
		break;
	}
fail:
	return ret;
}