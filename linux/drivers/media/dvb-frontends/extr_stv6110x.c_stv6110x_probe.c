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
struct stv6110x_state {TYPE_1__* i2c; int /*<<< orphan*/ * devctl; struct stv6110x_config* config; int /*<<< orphan*/  frontend; } ;
struct stv6110x_config {int /*<<< orphan*/  get_devctl; int /*<<< orphan*/  frontend; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_4__ {struct stv6110x_config* platform_data; } ;
struct i2c_client {TYPE_1__* adapter; TYPE_2__ dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct stv6110x_state*) ; 
 struct stv6110x_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st6110x_init_regs (struct stv6110x_state*) ; 
 int /*<<< orphan*/  stv6110x_ctl ; 
 int /*<<< orphan*/  stv6110x_get_devctl ; 
 int /*<<< orphan*/  stv6110x_set_frontend_opts (struct stv6110x_state*) ; 
 int /*<<< orphan*/  stv6110x_setup_divider (struct stv6110x_state*) ; 

__attribute__((used)) static int stv6110x_probe(struct i2c_client *client,
			  const struct i2c_device_id *id)
{
	struct stv6110x_config *config = client->dev.platform_data;

	struct stv6110x_state *stv6110x;

	stv6110x = kzalloc(sizeof(*stv6110x), GFP_KERNEL);
	if (!stv6110x)
		return -ENOMEM;

	stv6110x->frontend	= config->frontend;
	stv6110x->i2c		= client->adapter;
	stv6110x->config	= config;
	stv6110x->devctl	= &stv6110x_ctl;

	st6110x_init_regs(stv6110x);
	stv6110x_setup_divider(stv6110x);
	stv6110x_set_frontend_opts(stv6110x);

	dev_info(&stv6110x->i2c->dev, "Probed STV6110x\n");

	i2c_set_clientdata(client, stv6110x);

	/* setup callbacks */
	config->get_devctl = stv6110x_get_devctl;

	return 0;
}