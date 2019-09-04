#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ngene_channel {TYPE_4__* fe; TYPE_2__* dev; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_frontend {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (TYPE_4__*,int) ;} ;
struct TYPE_10__ {TYPE_1__ ops; } ;
struct TYPE_9__ {struct device dev; } ;
struct TYPE_8__ {TYPE_3__* pci_dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct dvb_frontend* dvb_attach (int /*<<< orphan*/ ,TYPE_4__*,struct i2c_adapter*,int) ; 
 struct i2c_adapter* i2c_adapter_from_chan (struct ngene_channel*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,int) ; 
 int /*<<< orphan*/  tda18271c2dd_attach ; 

__attribute__((used)) static int tuner_attach_tda18271(struct ngene_channel *chan)
{
	struct device *pdev = &chan->dev->pci_dev->dev;
	struct i2c_adapter *i2c = i2c_adapter_from_chan(chan);
	struct dvb_frontend *fe;

	if (chan->fe->ops.i2c_gate_ctrl)
		chan->fe->ops.i2c_gate_ctrl(chan->fe, 1);
	fe = dvb_attach(tda18271c2dd_attach, chan->fe, i2c, 0x60);
	if (chan->fe->ops.i2c_gate_ctrl)
		chan->fe->ops.i2c_gate_ctrl(chan->fe, 0);
	if (!fe) {
		dev_err(pdev, "No TDA18271 found!\n");
		return -ENODEV;
	}

	return 0;
}