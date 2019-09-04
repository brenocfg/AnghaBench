#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct i2c_adapter {int dummy; } ;
struct device {int dummy; } ;
struct ddb_input {int nr; TYPE_3__* port; } ;
struct ddb_dvb {TYPE_5__* fe; int /*<<< orphan*/  i2c_gate_ctrl; } ;
struct TYPE_9__ {int /*<<< orphan*/  i2c_gate_ctrl; } ;
struct TYPE_10__ {TYPE_4__ ops; struct ddb_input* sec_priv; } ;
struct TYPE_8__ {TYPE_2__* dev; struct ddb_dvb* dvb; TYPE_1__* i2c; } ;
struct TYPE_7__ {struct device* dev; } ;
struct TYPE_6__ {struct i2c_adapter adap; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/ * ddb_stv0367_config ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 TYPE_5__* dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct i2c_adapter*) ; 
 int /*<<< orphan*/  locked_gate_ctrl ; 
 int /*<<< orphan*/  stv0367ddb_attach ; 

__attribute__((used)) static int demod_attach_stv0367(struct ddb_input *input)
{
	struct i2c_adapter *i2c = &input->port->i2c->adap;
	struct ddb_dvb *dvb = &input->port->dvb[input->nr & 1];
	struct device *dev = input->port->dev->dev;

	/* attach frontend */
	dvb->fe = dvb_attach(stv0367ddb_attach,
			     &ddb_stv0367_config[(input->nr & 1)], i2c);

	if (!dvb->fe) {
		dev_err(dev, "No stv0367 found!\n");
		return -ENODEV;
	}
	dvb->fe->sec_priv = input;
	dvb->i2c_gate_ctrl = dvb->fe->ops.i2c_gate_ctrl;
	dvb->fe->ops.i2c_gate_ctrl = locked_gate_ctrl;
	return 0;
}