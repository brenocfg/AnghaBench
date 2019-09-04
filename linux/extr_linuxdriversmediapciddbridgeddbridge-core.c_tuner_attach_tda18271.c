#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct i2c_adapter {int dummy; } ;
struct dvb_frontend {int dummy; } ;
struct device {int dummy; } ;
struct ddb_input {int nr; TYPE_3__* port; } ;
struct ddb_dvb {TYPE_5__* fe; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (TYPE_5__*,int) ;} ;
struct TYPE_12__ {TYPE_4__ ops; } ;
struct TYPE_10__ {TYPE_2__* dev; struct ddb_dvb* dvb; TYPE_1__* i2c; } ;
struct TYPE_9__ {struct device* dev; } ;
struct TYPE_8__ {struct i2c_adapter adap; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct dvb_frontend* dvb_attach (int /*<<< orphan*/ ,TYPE_5__*,struct i2c_adapter*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,int) ; 
 int /*<<< orphan*/  tda18271c2dd_attach ; 

__attribute__((used)) static int tuner_attach_tda18271(struct ddb_input *input)
{
	struct i2c_adapter *i2c = &input->port->i2c->adap;
	struct ddb_dvb *dvb = &input->port->dvb[input->nr & 1];
	struct device *dev = input->port->dev->dev;
	struct dvb_frontend *fe;

	if (dvb->fe->ops.i2c_gate_ctrl)
		dvb->fe->ops.i2c_gate_ctrl(dvb->fe, 1);
	fe = dvb_attach(tda18271c2dd_attach, dvb->fe, i2c, 0x60);
	if (dvb->fe->ops.i2c_gate_ctrl)
		dvb->fe->ops.i2c_gate_ctrl(dvb->fe, 0);
	if (!fe) {
		dev_err(dev, "No TDA18271 found!\n");
		return -ENODEV;
	}
	return 0;
}