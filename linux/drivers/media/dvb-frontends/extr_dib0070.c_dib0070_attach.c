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
struct dvb_frontend {struct dib0070_state* tuner_priv; TYPE_1__ ops; } ;
struct dib0070_state {int /*<<< orphan*/  i2c_buffer_lock; struct dvb_frontend* fe; struct i2c_adapter* i2c; struct dib0070_config* cfg; } ;
struct dib0070_config {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dib0070_ops ; 
 scalar_t__ dib0070_reset (struct dvb_frontend*) ; 
 int /*<<< orphan*/  kfree (struct dib0070_state*) ; 
 struct dib0070_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

struct dvb_frontend *dib0070_attach(struct dvb_frontend *fe, struct i2c_adapter *i2c, struct dib0070_config *cfg)
{
	struct dib0070_state *state = kzalloc(sizeof(struct dib0070_state), GFP_KERNEL);
	if (state == NULL)
		return NULL;

	state->cfg = cfg;
	state->i2c = i2c;
	state->fe  = fe;
	mutex_init(&state->i2c_buffer_lock);
	fe->tuner_priv = state;

	if (dib0070_reset(fe) != 0)
		goto free_mem;

	pr_info("DiB0070: successfully identified\n");
	memcpy(&fe->ops.tuner_ops, &dib0070_ops, sizeof(struct dvb_tuner_ops));

	fe->tuner_priv = state;
	return fe;

free_mem:
	kfree(state);
	fe->tuner_priv = NULL;
	return NULL;
}