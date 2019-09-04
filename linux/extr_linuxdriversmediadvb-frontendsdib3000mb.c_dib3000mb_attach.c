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
struct i2c_adapter {int dummy; } ;
struct dvb_frontend_ops {int dummy; } ;
struct dvb_frontend {struct dib3000_state* demodulator_priv; int /*<<< orphan*/  ops; } ;
struct dib_fe_xfer_ops {int /*<<< orphan*/  tuner_pass_ctrl; int /*<<< orphan*/  pid_ctrl; int /*<<< orphan*/  fifo_ctrl; int /*<<< orphan*/  pid_parse; } ;
struct dib3000_state {struct dvb_frontend frontend; int /*<<< orphan*/  config; struct i2c_adapter* i2c; } ;
struct dib3000_config {int dummy; } ;

/* Variables and functions */
 scalar_t__ DIB3000MB_DEVICE_ID ; 
 scalar_t__ DIB3000_I2C_ID_DIBCOM ; 
 int /*<<< orphan*/  DIB3000_REG_DEVICE_ID ; 
 int /*<<< orphan*/  DIB3000_REG_MANUFACTOR_ID ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dib3000mb_fifo_control ; 
 struct dib3000_config const dib3000mb_ops ; 
 int /*<<< orphan*/  dib3000mb_pid_control ; 
 int /*<<< orphan*/  dib3000mb_pid_parse ; 
 int /*<<< orphan*/  dib3000mb_tuner_pass_ctrl ; 
 int /*<<< orphan*/  kfree (struct dib3000_state*) ; 
 struct dib3000_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct dib3000_config const*,int) ; 
 scalar_t__ rd (int /*<<< orphan*/ ) ; 

struct dvb_frontend* dib3000mb_attach(const struct dib3000_config* config,
				      struct i2c_adapter* i2c, struct dib_fe_xfer_ops *xfer_ops)
{
	struct dib3000_state* state = NULL;

	/* allocate memory for the internal state */
	state = kzalloc(sizeof(struct dib3000_state), GFP_KERNEL);
	if (state == NULL)
		goto error;

	/* setup the state */
	state->i2c = i2c;
	memcpy(&state->config,config,sizeof(struct dib3000_config));

	/* check for the correct demod */
	if (rd(DIB3000_REG_MANUFACTOR_ID) != DIB3000_I2C_ID_DIBCOM)
		goto error;

	if (rd(DIB3000_REG_DEVICE_ID) != DIB3000MB_DEVICE_ID)
		goto error;

	/* create dvb_frontend */
	memcpy(&state->frontend.ops, &dib3000mb_ops, sizeof(struct dvb_frontend_ops));
	state->frontend.demodulator_priv = state;

	/* set the xfer operations */
	xfer_ops->pid_parse = dib3000mb_pid_parse;
	xfer_ops->fifo_ctrl = dib3000mb_fifo_control;
	xfer_ops->pid_ctrl = dib3000mb_pid_control;
	xfer_ops->tuner_pass_ctrl = dib3000mb_tuner_pass_ctrl;

	return &state->frontend;

error:
	kfree(state);
	return NULL;
}