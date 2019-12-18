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
struct i2c_adapter {int dummy; } ;
struct dvb_tuner_ops {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tuner_ops; } ;
struct dvb_frontend {struct cx24113_state* tuner_priv; TYPE_1__ ops; } ;
struct cx24113_state {int rev; void* ver; struct i2c_adapter* i2c; struct cx24113_config const* config; } ;
struct cx24113_config {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  REV_CX24113 128 
 void* cx24113_readreg (struct cx24113_state*,int) ; 
 int /*<<< orphan*/  cx24113_tuner_ops ; 
 int /*<<< orphan*/  cx_err (char*,int) ; 
 int /*<<< orphan*/  cx_info (char*,...) ; 
 int /*<<< orphan*/  kfree (struct cx24113_state*) ; 
 struct cx24113_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

struct dvb_frontend *cx24113_attach(struct dvb_frontend *fe,
		const struct cx24113_config *config, struct i2c_adapter *i2c)
{
	/* allocate memory for the internal state */
	struct cx24113_state *state = kzalloc(sizeof(*state), GFP_KERNEL);
	int rc;

	if (!state)
		return NULL;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;

	cx_info("trying to detect myself\n");

	/* making a dummy read, because of some expected troubles
	 * after power on */
	cx24113_readreg(state, 0x00);

	rc = cx24113_readreg(state, 0x00);
	if (rc < 0) {
		cx_info("CX24113 not found.\n");
		goto error;
	}
	state->rev = rc;

	switch (rc) {
	case 0x43:
		cx_info("detected CX24113 variant\n");
		break;
	case REV_CX24113:
		cx_info("successfully detected\n");
		break;
	default:
		cx_err("unsupported device id: %x\n", state->rev);
		goto error;
	}
	state->ver = cx24113_readreg(state, 0x01);
	cx_info("version: %x\n", state->ver);

	/* create dvb_frontend */
	memcpy(&fe->ops.tuner_ops, &cx24113_tuner_ops,
			sizeof(struct dvb_tuner_ops));
	fe->tuner_priv = state;
	return fe;

error:
	kfree(state);

	return NULL;
}