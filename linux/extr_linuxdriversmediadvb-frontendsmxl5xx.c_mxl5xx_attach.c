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
typedef  void* u32 ;
struct dvb_frontend {struct mxl_base* demodulator_priv; int /*<<< orphan*/  ops; } ;
struct mxl_base {int tuner_in_use; int count; int demod_num; int* xbar; struct dvb_frontend fe; int /*<<< orphan*/  mxls; int /*<<< orphan*/  mxl; int /*<<< orphan*/  mxllist; struct mxl_base* base; int /*<<< orphan*/  tune_lock; int /*<<< orphan*/  status_lock; int /*<<< orphan*/  i2c_lock; int /*<<< orphan*/  type; int /*<<< orphan*/  adr; struct i2c_adapter* i2c; int /*<<< orphan*/ * i2cdev; void* tuner; void* demod; } ;
struct mxl5xx_cfg {int /*<<< orphan*/  type; int /*<<< orphan*/  adr; } ;
struct mxl {int tuner_in_use; int count; int demod_num; int* xbar; struct dvb_frontend fe; int /*<<< orphan*/  mxls; int /*<<< orphan*/  mxl; int /*<<< orphan*/  mxllist; struct mxl* base; int /*<<< orphan*/  tune_lock; int /*<<< orphan*/  status_lock; int /*<<< orphan*/  i2c_lock; int /*<<< orphan*/  type; int /*<<< orphan*/  adr; struct i2c_adapter* i2c; int /*<<< orphan*/ * i2cdev; void* tuner; void* demod; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mxl_base*) ; 
 struct mxl_base* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mxl_base* match_base (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mxl_ops ; 
 int /*<<< orphan*/  mxllist ; 
 scalar_t__ probe (struct mxl_base*,struct mxl5xx_cfg*) ; 
 int set_input (struct dvb_frontend*,int) ; 

struct dvb_frontend *mxl5xx_attach(struct i2c_adapter *i2c,
	struct mxl5xx_cfg *cfg, u32 demod, u32 tuner,
	int (**fn_set_input)(struct dvb_frontend *, int))
{
	struct mxl *state;
	struct mxl_base *base;

	state = kzalloc(sizeof(struct mxl), GFP_KERNEL);
	if (!state)
		return NULL;

	state->demod = demod;
	state->tuner = tuner;
	state->tuner_in_use = 0xffffffff;
	state->i2cdev = &i2c->dev;

	base = match_base(i2c, cfg->adr);
	if (base) {
		base->count++;
		if (base->count > base->demod_num)
			goto fail;
		state->base = base;
	} else {
		base = kzalloc(sizeof(struct mxl_base), GFP_KERNEL);
		if (!base)
			goto fail;
		base->i2c = i2c;
		base->adr = cfg->adr;
		base->type = cfg->type;
		base->count = 1;
		mutex_init(&base->i2c_lock);
		mutex_init(&base->status_lock);
		mutex_init(&base->tune_lock);
		INIT_LIST_HEAD(&base->mxls);

		state->base = base;
		if (probe(state, cfg) < 0) {
			kfree(base);
			goto fail;
		}
		list_add(&base->mxllist, &mxllist);
	}
	state->fe.ops               = mxl_ops;
	state->xbar[0]              = 4;
	state->xbar[1]              = demod;
	state->xbar[2]              = 8;
	state->fe.demodulator_priv  = state;
	*fn_set_input               = set_input;

	list_add(&state->mxl, &base->mxls);
	return &state->fe;

fail:
	kfree(state);
	return NULL;
}