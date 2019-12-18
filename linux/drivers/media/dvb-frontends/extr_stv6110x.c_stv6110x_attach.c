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
struct stv6110x_state {struct stv6110x_devctl const* devctl; struct i2c_adapter* i2c; struct stv6110x_config const* config; struct dvb_frontend* frontend; } ;
struct stv6110x_devctl {int dummy; } ;
struct stv6110x_config {int dummy; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  tuner_ops; } ;
struct dvb_frontend {TYPE_1__ ops; struct stv6110x_state* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct stv6110x_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st6110x_init_regs (struct stv6110x_state*) ; 
 struct stv6110x_devctl const stv6110x_ctl ; 
 int /*<<< orphan*/  stv6110x_ops ; 
 int /*<<< orphan*/  stv6110x_set_frontend_opts (struct stv6110x_state*) ; 
 int /*<<< orphan*/  stv6110x_setup_divider (struct stv6110x_state*) ; 

const struct stv6110x_devctl *stv6110x_attach(struct dvb_frontend *fe,
					const struct stv6110x_config *config,
					struct i2c_adapter *i2c)
{
	struct stv6110x_state *stv6110x;

	stv6110x = kzalloc(sizeof(*stv6110x), GFP_KERNEL);
	if (!stv6110x)
		return NULL;

	stv6110x->frontend	= fe;
	stv6110x->i2c		= i2c;
	stv6110x->config	= config;
	stv6110x->devctl	= &stv6110x_ctl;

	st6110x_init_regs(stv6110x);
	stv6110x_setup_divider(stv6110x);
	stv6110x_set_frontend_opts(stv6110x);

	fe->tuner_priv		= stv6110x;
	fe->ops.tuner_ops	= stv6110x_ops;

	dev_info(&stv6110x->i2c->dev, "Attaching STV6110x\n");
	return stv6110x->devctl;
}