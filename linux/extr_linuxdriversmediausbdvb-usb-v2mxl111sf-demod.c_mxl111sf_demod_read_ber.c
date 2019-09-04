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
typedef  int /*<<< orphan*/  u32 ;
struct mxl111sf_demod_state {int dummy; } ;
struct dvb_frontend {struct mxl111sf_demod_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALCULATE_BER (int,int) ; 
 int /*<<< orphan*/  V6_N_ACCUMULATE_REG ; 
 int /*<<< orphan*/  V6_RS_AVG_ERRORS_LSB_REG ; 
 int /*<<< orphan*/  V6_RS_AVG_ERRORS_MSB_REG ; 
 int mxl111sf_demod_read_reg (struct mxl111sf_demod_state*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ mxl_fail (int) ; 

__attribute__((used)) static int mxl111sf_demod_read_ber(struct dvb_frontend *fe, u32 *ber)
{
	struct mxl111sf_demod_state *state = fe->demodulator_priv;
	u8 val1, val2, val3;
	int ret;

	*ber = 0;

	ret = mxl111sf_demod_read_reg(state, V6_RS_AVG_ERRORS_LSB_REG, &val1);
	if (mxl_fail(ret))
		goto fail;
	ret = mxl111sf_demod_read_reg(state, V6_RS_AVG_ERRORS_MSB_REG, &val2);
	if (mxl_fail(ret))
		goto fail;
	ret = mxl111sf_demod_read_reg(state, V6_N_ACCUMULATE_REG, &val3);
	if (mxl_fail(ret))
		goto fail;

	*ber = CALCULATE_BER((val1 | (val2 << 8)), val3);
fail:
	return ret;
}