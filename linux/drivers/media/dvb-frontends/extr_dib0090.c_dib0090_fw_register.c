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
struct dvb_frontend {struct dib0090_fw_state* tuner_priv; TYPE_1__ ops; } ;
struct dib0090_fw_state {struct dib0090_config const* config; int /*<<< orphan*/  i2c_buffer_lock; struct dvb_frontend* fe; struct i2c_adapter* i2c; } ;
struct dib0090_config {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dib0090_fw_ops ; 
 scalar_t__ dib0090_fw_reset_digital (struct dvb_frontend*,struct dib0090_config const*) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  kfree (struct dib0090_fw_state*) ; 
 struct dib0090_fw_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

struct dvb_frontend *dib0090_fw_register(struct dvb_frontend *fe, struct i2c_adapter *i2c, const struct dib0090_config *config)
{
	struct dib0090_fw_state *st = kzalloc(sizeof(struct dib0090_fw_state), GFP_KERNEL);
	if (st == NULL)
		return NULL;

	st->config = config;
	st->i2c = i2c;
	st->fe = fe;
	mutex_init(&st->i2c_buffer_lock);
	fe->tuner_priv = st;

	if (dib0090_fw_reset_digital(fe, st->config) != 0)
		goto free_mem;

	dprintk("DiB0090 FW: successfully identified\n");
	memcpy(&fe->ops.tuner_ops, &dib0090_fw_ops, sizeof(struct dvb_tuner_ops));

	return fe;
free_mem:
	kfree(st);
	fe->tuner_priv = NULL;
	return NULL;
}