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
typedef  enum fe_modulation { ____Placeholder_fe_modulation } fe_modulation ;

/* Variables and functions */
 int QAM_16 ; 
 int QAM_64 ; 
 int QPSK ; 
 int /*<<< orphan*/  V6_MODORDER_TPS_REG ; 
 int V6_PARAM_CONSTELLATION_MASK ; 
 int mxl111sf_demod_read_reg (struct mxl111sf_demod_state*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ mxl_fail (int) ; 

__attribute__((used)) static
int mxl1x1sf_demod_get_tps_modulation(struct mxl111sf_demod_state *state,
				      enum fe_modulation *modulation)
{
	u8 val;
	int ret = mxl111sf_demod_read_reg(state, V6_MODORDER_TPS_REG, &val);
	/* Constellation, 00 : QPSK, 01 : 16QAM, 10:64QAM */
	if (mxl_fail(ret))
		goto fail;

	switch ((val & V6_PARAM_CONSTELLATION_MASK) >> 4) {
	case 0:
		*modulation = QPSK;
		break;
	case 1:
		*modulation = QAM_16;
		break;
	case 2:
		*modulation = QAM_64;
		break;
	}
fail:
	return ret;
}