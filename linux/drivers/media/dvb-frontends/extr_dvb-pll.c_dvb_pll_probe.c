#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct i2c_device_id {scalar_t__ driver_data; } ;
struct TYPE_6__ {struct dvb_pll_config* platform_data; } ;
struct i2c_client {TYPE_3__ dev; int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;
struct dvb_pll_config {struct dvb_frontend* fe; } ;
struct TYPE_4__ {int /*<<< orphan*/ * release; } ;
struct TYPE_5__ {TYPE_1__ tuner_ops; } ;
struct dvb_frontend {TYPE_2__ ops; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dev_info (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dvb_pll_attach (struct dvb_frontend*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct dvb_frontend*) ; 

__attribute__((used)) static int
dvb_pll_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct dvb_pll_config *cfg;
	struct dvb_frontend *fe;
	unsigned int desc_id;

	cfg = client->dev.platform_data;
	fe = cfg->fe;
	i2c_set_clientdata(client, fe);
	desc_id = (unsigned int) id->driver_data;

	if (!dvb_pll_attach(fe, client->addr, client->adapter, desc_id))
		return -ENOMEM;

	/*
	 * Unset tuner_ops.release (== dvb_pll_release)
	 * which has been just set in the above dvb_pll_attach(),
	 * because if tuner_ops.release was left defined,
	 * this module would be 'put' twice on exit:
	 * once by dvb_frontend_detach() and another by dvb_module_release().
	 *
	 * dvb_pll_release is instead executed in the i2c driver's .remove(),
	 * keeping dvb_pll_attach untouched for legacy (dvb_attach) drivers.
	 */
	fe->ops.tuner_ops.release = NULL;
	dev_info(&client->dev, "DVB Simple Tuner attached.\n");
	return 0;
}