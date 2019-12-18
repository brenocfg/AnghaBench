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
struct TYPE_4__ {struct stv090x_state* demodulator_priv; int /*<<< orphan*/  ops; } ;
struct stv090x_state {int /*<<< orphan*/  rolloff; int /*<<< orphan*/  device; int /*<<< orphan*/  demod_mode; int /*<<< orphan*/  demod; TYPE_2__ frontend; int /*<<< orphan*/  i2c; struct stv090x_config* config; int /*<<< orphan*/ * verbose; } ;
struct stv090x_config {int /*<<< orphan*/  get_dvb_frontend; int /*<<< orphan*/  device; int /*<<< orphan*/  demod_mode; int /*<<< orphan*/  demod; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_3__ {struct stv090x_config* platform_data; } ;
struct i2c_client {int /*<<< orphan*/  adapter; TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  STV090x_RO_35 ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct stv090x_state*) ; 
 int /*<<< orphan*/  kfree (struct stv090x_state*) ; 
 struct stv090x_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stv090x_get_dvb_frontend ; 
 int /*<<< orphan*/  stv090x_ops ; 
 int stv090x_setup_compound (struct stv090x_state*) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int stv090x_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	int ret = 0;
	struct stv090x_config *config = client->dev.platform_data;

	struct stv090x_state *state = NULL;

	state = kzalloc(sizeof(*state), GFP_KERNEL);
	if (!state) {
		ret = -ENOMEM;
		goto error;
	}

	state->verbose				= &verbose;
	state->config				= config;
	state->i2c				= client->adapter;
	state->frontend.ops			= stv090x_ops;
	state->frontend.demodulator_priv	= state;
	state->demod				= config->demod;
						/* Single or Dual mode */
	state->demod_mode			= config->demod_mode;
	state->device				= config->device;
						/* default */
	state->rolloff				= STV090x_RO_35;

	ret = stv090x_setup_compound(state);
	if (ret)
		goto error;

	i2c_set_clientdata(client, state);

	/* setup callbacks */
	config->get_dvb_frontend = stv090x_get_dvb_frontend;

	return 0;

error:
	kfree(state);
	return ret;
}