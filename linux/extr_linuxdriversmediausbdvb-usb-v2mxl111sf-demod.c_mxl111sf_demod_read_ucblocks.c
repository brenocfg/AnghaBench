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
typedef  int u32 ;
struct mxl111sf_demod_state {int dummy; } ;
struct dvb_frontend {struct mxl111sf_demod_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  V6_FEC_PER_COUNT_REG ; 
 int V6_FEC_PER_SCALE_MASK ; 
 int /*<<< orphan*/  V6_FEC_PER_SCALE_REG ; 
 int mxl111sf_demod_read_reg (struct mxl111sf_demod_state*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ mxl_fail (int) ; 

__attribute__((used)) static int mxl111sf_demod_read_ucblocks(struct dvb_frontend *fe, u32 *ucblocks)
{
	struct mxl111sf_demod_state *state = fe->demodulator_priv;
	u32 fec_per_count, fec_per_scale;
	u8 val;
	int ret;

	*ucblocks = 0;

	/* FEC_PER_COUNT Register */
	ret = mxl111sf_demod_read_reg(state, V6_FEC_PER_COUNT_REG, &val);
	if (mxl_fail(ret))
		goto fail;

	fec_per_count = val;

	/* FEC_PER_SCALE Register */
	ret = mxl111sf_demod_read_reg(state, V6_FEC_PER_SCALE_REG, &val);
	if (mxl_fail(ret))
		goto fail;

	val &= V6_FEC_PER_SCALE_MASK;
	val *= 4;

	fec_per_scale = 1 << val;

	fec_per_count *= fec_per_scale;

	*ucblocks = fec_per_count;
fail:
	return ret;
}