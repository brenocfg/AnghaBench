#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {int demod_chip; int /*<<< orphan*/  get_dvb_frontend; } ;
struct TYPE_5__ {struct lgdt330x_state* demodulator_priv; TYPE_2__ ops; } ;
struct lgdt330x_state {int current_frequency; int current_modulation; TYPE_2__ config; struct i2c_client* client; TYPE_1__ frontend; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/ * platform_data; } ;
struct i2c_client {TYPE_3__ dev; } ;
struct dvb_frontend_ops {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
#define  LGDT3302 129 
#define  LGDT3303 128 
 scalar_t__ debug ; 
 int /*<<< orphan*/  dev_info (TYPE_3__*,char*,char*) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,TYPE_3__*,char*) ; 
 scalar_t__ i2c_read_demod_bytes (struct lgdt330x_state*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct lgdt330x_state*) ; 
 int /*<<< orphan*/  kfree (struct lgdt330x_state*) ; 
 struct lgdt330x_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lgdt3302_ops ; 
 int /*<<< orphan*/  lgdt3303_ops ; 
 int /*<<< orphan*/  lgdt330x_get_dvb_frontend ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int lgdt330x_probe(struct i2c_client *client,
			  const struct i2c_device_id *id)
{
	struct lgdt330x_state *state = NULL;
	u8 buf[1];

	/* Allocate memory for the internal state */
	state = kzalloc(sizeof(*state), GFP_KERNEL);
	if (!state)
		goto error;

	/* Setup the state */
	memcpy(&state->config, client->dev.platform_data,
	       sizeof(state->config));
	i2c_set_clientdata(client, state);
	state->client = client;

	/* Create dvb_frontend */
	switch (state->config.demod_chip) {
	case LGDT3302:
		memcpy(&state->frontend.ops, &lgdt3302_ops,
		       sizeof(struct dvb_frontend_ops));
		break;
	case LGDT3303:
		memcpy(&state->frontend.ops, &lgdt3303_ops,
		       sizeof(struct dvb_frontend_ops));
		break;
	default:
		goto error;
	}
	state->frontend.demodulator_priv = state;

	/* Setup get frontend callback */
	state->config.get_dvb_frontend = lgdt330x_get_dvb_frontend;

	/* Verify communication with demod chip */
	if (i2c_read_demod_bytes(state, 2, buf, 1))
		goto error;

	state->current_frequency = -1;
	state->current_modulation = -1;

	dev_info(&state->client->dev,
		"Demod loaded for LGDT330%s chip\n",
		state->config.demod_chip == LGDT3302 ? "2" : "3");

	return 0;

error:
	kfree(state);
	if (debug)
		dev_printk(KERN_DEBUG, &client->dev, "Error loading lgdt330x driver\n");
	return -ENODEV;
}