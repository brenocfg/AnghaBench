#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  caps; } ;
struct TYPE_4__ {TYPE_1__ info; } ;
struct dvb_frontend {TYPE_2__ ops; struct stv090x_state* demodulator_priv; } ;
struct stv090x_state {int demod; scalar_t__ demod_mode; scalar_t__ device; int num_used; int dev_ver; struct stv090x_state* internal; struct dvb_frontend frontend; int /*<<< orphan*/  tuner_lock; int /*<<< orphan*/  demod_lock; struct stv090x_config* config; int /*<<< orphan*/  i2c_addr; struct i2c_adapter* i2c; struct i2c_adapter* i2c_adap; scalar_t__ mclk; int /*<<< orphan*/  rolloff; int /*<<< orphan*/ * verbose; } ;
struct stv090x_internal {int dummy; } ;
struct stv090x_dev {struct stv090x_state* internal; } ;
struct stv090x_config {scalar_t__ demod_mode; scalar_t__ device; int /*<<< orphan*/  set_gpio; scalar_t__ diseqc_envelope_mode; int /*<<< orphan*/  address; } ;
struct i2c_adapter {int dummy; } ;
typedef  enum stv090x_demodulator { ____Placeholder_stv090x_demodulator } stv090x_demodulator ;

/* Variables and functions */
 int /*<<< orphan*/  FE_CAN_MULTISTREAM ; 
 int /*<<< orphan*/  FE_ERROR ; 
 int /*<<< orphan*/  FE_INFO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SEC_MINI_A ; 
 scalar_t__ STV0900 ; 
 scalar_t__ STV090x_DUAL ; 
 int /*<<< orphan*/  STV090x_RO_35 ; 
 struct stv090x_dev* append_internal (struct stv090x_state*) ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*,...) ; 
 struct stv090x_dev* find_dev (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct stv090x_state*) ; 
 struct stv090x_state* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct stv090x_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_dev (struct stv090x_state*) ; 
 TYPE_2__ stv090x_ops ; 
 int /*<<< orphan*/  stv090x_send_diseqc_burst (struct dvb_frontend*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stv090x_set_gpio ; 
 scalar_t__ stv090x_setup (struct dvb_frontend*) ; 
 int /*<<< orphan*/  verbose ; 

struct dvb_frontend *stv090x_attach(struct stv090x_config *config,
				    struct i2c_adapter *i2c,
				    enum stv090x_demodulator demod)
{
	struct stv090x_state *state = NULL;
	struct stv090x_dev *temp_int;

	state = kzalloc(sizeof (struct stv090x_state), GFP_KERNEL);
	if (state == NULL)
		goto error;

	state->verbose				= &verbose;
	state->config				= config;
	state->i2c				= i2c;
	state->frontend.ops			= stv090x_ops;
	state->frontend.demodulator_priv	= state;
	state->demod				= demod;
	state->demod_mode			= config->demod_mode; /* Single or Dual mode */
	state->device				= config->device;
	state->rolloff				= STV090x_RO_35; /* default */

	temp_int = find_dev(state->i2c,
				state->config->address);

	if ((temp_int != NULL) && (state->demod_mode == STV090x_DUAL)) {
		state->internal = temp_int->internal;
		state->internal->num_used++;
		dprintk(FE_INFO, 1, "Found Internal Structure!");
	} else {
		state->internal = kmalloc(sizeof(struct stv090x_internal),
					  GFP_KERNEL);
		if (!state->internal)
			goto error;
		temp_int = append_internal(state->internal);
		if (!temp_int) {
			kfree(state->internal);
			goto error;
		}
		state->internal->num_used = 1;
		state->internal->mclk = 0;
		state->internal->dev_ver = 0;
		state->internal->i2c_adap = state->i2c;
		state->internal->i2c_addr = state->config->address;
		dprintk(FE_INFO, 1, "Create New Internal Structure!");

		mutex_init(&state->internal->demod_lock);
		mutex_init(&state->internal->tuner_lock);

		if (stv090x_setup(&state->frontend) < 0) {
			dprintk(FE_ERROR, 1, "Error setting up device");
			goto err_remove;
		}
	}

	if (state->internal->dev_ver >= 0x30)
		state->frontend.ops.info.caps |= FE_CAN_MULTISTREAM;

	/* workaround for stuck DiSEqC output */
	if (config->diseqc_envelope_mode)
		stv090x_send_diseqc_burst(&state->frontend, SEC_MINI_A);

	config->set_gpio = stv090x_set_gpio;

	dprintk(FE_ERROR, 1, "Attaching %s demodulator(%d) Cut=0x%02x",
	       state->device == STV0900 ? "STV0900" : "STV0903",
	       demod,
	       state->internal->dev_ver);

	return &state->frontend;

err_remove:
	remove_dev(state->internal);
	kfree(state->internal);
error:
	kfree(state);
	return NULL;
}