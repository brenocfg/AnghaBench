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
typedef  int /*<<< orphan*/  u32 ;
struct mxl5007t_state {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;} ;
struct dvb_frontend {TYPE_1__ ops; struct mxl5007t_state* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  TUNER_STATUS_LOCKED ; 
 int mxl5007t_synth_lock_status (struct mxl5007t_state*,int*,int*) ; 
 int /*<<< orphan*/  mxl_debug (char*,char*,char*) ; 
 scalar_t__ mxl_fail (int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int) ; 

__attribute__((used)) static int mxl5007t_get_status(struct dvb_frontend *fe, u32 *status)
{
	struct mxl5007t_state *state = fe->tuner_priv;
	int rf_locked, ref_locked, ret;

	*status = 0;

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	ret = mxl5007t_synth_lock_status(state, &rf_locked, &ref_locked);
	if (mxl_fail(ret))
		goto fail;
	mxl_debug("%s%s", rf_locked ? "rf locked " : "",
		  ref_locked ? "ref locked" : "");

	if ((rf_locked) || (ref_locked))
		*status |= TUNER_STATUS_LOCKED;
fail:
	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	return ret;
}