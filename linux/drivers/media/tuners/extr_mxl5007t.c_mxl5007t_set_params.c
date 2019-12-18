#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mxl5007t_state {int frequency; int /*<<< orphan*/  lock; int /*<<< orphan*/  bandwidth; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;} ;
struct dtv_frontend_properties {int delivery_system; int frequency; int /*<<< orphan*/  bandwidth_hz; } ;
struct dvb_frontend {TYPE_1__ ops; struct mxl5007t_state* tuner_priv; struct dtv_frontend_properties dtv_property_cache; } ;
typedef  enum mxl5007t_mode { ____Placeholder_mxl5007t_mode } mxl5007t_mode ;
typedef  enum mxl5007t_bw_mhz { ____Placeholder_mxl5007t_bw_mhz } mxl5007t_bw_mhz ;

/* Variables and functions */
 int EINVAL ; 
 int MxL_BW_6MHz ; 
 int MxL_BW_7MHz ; 
 int MxL_BW_8MHz ; 
 int MxL_MODE_ATSC ; 
 int MxL_MODE_CABLE ; 
 int MxL_MODE_DVBT ; 
#define  SYS_ATSC 131 
#define  SYS_DVBC_ANNEX_B 130 
#define  SYS_DVBT 129 
#define  SYS_DVBT2 128 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int mxl5007t_tuner_init (struct mxl5007t_state*,int) ; 
 int mxl5007t_tuner_rf_tune (struct mxl5007t_state*,int,int) ; 
 int /*<<< orphan*/  mxl_err (char*) ; 
 scalar_t__ mxl_fail (int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int) ; 

__attribute__((used)) static int mxl5007t_set_params(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	u32 delsys = c->delivery_system;
	struct mxl5007t_state *state = fe->tuner_priv;
	enum mxl5007t_bw_mhz bw;
	enum mxl5007t_mode mode;
	int ret;
	u32 freq = c->frequency;

	switch (delsys) {
	case SYS_ATSC:
		mode = MxL_MODE_ATSC;
		bw = MxL_BW_6MHz;
		break;
	case SYS_DVBC_ANNEX_B:
		mode = MxL_MODE_CABLE;
		bw = MxL_BW_6MHz;
		break;
	case SYS_DVBT:
	case SYS_DVBT2:
		mode = MxL_MODE_DVBT;
		switch (c->bandwidth_hz) {
		case 6000000:
			bw = MxL_BW_6MHz;
			break;
		case 7000000:
			bw = MxL_BW_7MHz;
			break;
		case 8000000:
			bw = MxL_BW_8MHz;
			break;
		default:
			return -EINVAL;
		}
		break;
	default:
		mxl_err("modulation type not supported!");
		return -EINVAL;
	}

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	mutex_lock(&state->lock);

	ret = mxl5007t_tuner_init(state, mode);
	if (mxl_fail(ret))
		goto fail;

	ret = mxl5007t_tuner_rf_tune(state, freq, bw);
	if (mxl_fail(ret))
		goto fail;

	state->frequency = freq;
	state->bandwidth = c->bandwidth_hz;
fail:
	mutex_unlock(&state->lock);

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	return ret;
}