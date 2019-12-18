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
typedef  int u16 ;
struct mxl111sf_tuner_state {int dummy; } ;
struct dvb_frontend {struct mxl111sf_tuner_state* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  V6_DIG_RF_PWR_LSB_REG ; 
 int /*<<< orphan*/  V6_DIG_RF_PWR_MSB_REG ; 
 int mxl111sf_tuner_read_reg (struct mxl111sf_tuner_state*,int /*<<< orphan*/ ,int*) ; 
 int mxl111sf_tuner_write_reg (struct mxl111sf_tuner_state*,int,int) ; 
 scalar_t__ mxl_fail (int) ; 

__attribute__((used)) static int mxl111sf_get_rf_strength(struct dvb_frontend *fe, u16 *strength)
{
	struct mxl111sf_tuner_state *state = fe->tuner_priv;
	u8 val1, val2;
	int ret;

	*strength = 0;

	ret = mxl111sf_tuner_write_reg(state, 0x00, 0x02);
	if (mxl_fail(ret))
		goto fail;
	ret = mxl111sf_tuner_read_reg(state, V6_DIG_RF_PWR_LSB_REG, &val1);
	if (mxl_fail(ret))
		goto fail;
	ret = mxl111sf_tuner_read_reg(state, V6_DIG_RF_PWR_MSB_REG, &val2);
	if (mxl_fail(ret))
		goto fail;

	*strength = val1 | ((val2 & 0x07) << 8);
fail:
	ret = mxl111sf_tuner_write_reg(state, 0x00, 0x00);
	mxl_fail(ret);

	return ret;
}