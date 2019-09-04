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
struct drxk_config {int adr; char* microcode_name; } ;
struct device {int dummy; } ;
struct ddb_input {int nr; TYPE_3__* port; } ;
struct ddb_dvb {TYPE_5__* fe; int /*<<< orphan*/  i2c_gate_ctrl; } ;
typedef  int /*<<< orphan*/  config ;
struct TYPE_9__ {int /*<<< orphan*/  i2c_gate_ctrl; } ;
struct TYPE_10__ {TYPE_4__ ops; struct ddb_input* sec_priv; } ;
struct TYPE_8__ {TYPE_2__* dev; struct ddb_dvb* dvb; TYPE_1__* i2c; } ;
struct TYPE_7__ {struct device* dev; } ;
struct TYPE_6__ {struct i2c_adapter adap; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  drxk_attach ; 
 TYPE_5__* dvb_attach (int /*<<< orphan*/ ,struct drxk_config*,struct i2c_adapter*) ; 
 int /*<<< orphan*/  locked_gate_ctrl ; 
 int /*<<< orphan*/  memset (struct drxk_config*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int demod_attach_drxk(struct ddb_input *input)
{
	struct i2c_adapter *i2c = &input->port->i2c->adap;
	struct ddb_dvb *dvb = &input->port->dvb[input->nr & 1];
	struct device *dev = input->port->dev->dev;
	struct drxk_config config;

	memset(&config, 0, sizeof(config));
	config.adr = 0x29 + (input->nr & 1);
	config.microcode_name = "drxk_a3.mc";

	dvb->fe = dvb_attach(drxk_attach, &config, i2c);
	if (!dvb->fe) {
		dev_err(dev, "No DRXK found!\n");
		return -ENODEV;
	}
	dvb->fe->sec_priv = input;
	dvb->i2c_gate_ctrl = dvb->fe->ops.i2c_gate_ctrl;
	dvb->fe->ops.i2c_gate_ctrl = locked_gate_ctrl;
	return 0;
}