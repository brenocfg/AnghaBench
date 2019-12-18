#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ngene_channel {int number; TYPE_4__* fe; int /*<<< orphan*/  gate_ctrl; TYPE_3__* dev; } ;
struct i2c_adapter {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  i2c_gate_ctrl; } ;
struct TYPE_8__ {TYPE_1__ ops; struct ngene_channel* sec_priv; } ;
struct TYPE_7__ {TYPE_2__* pci_dev; } ;
struct TYPE_6__ {struct device dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/ * ddb_stv0367_config ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  drxk_gate_ctrl ; 
 TYPE_4__* dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct i2c_adapter*) ; 
 int /*<<< orphan*/  stv0367ddb_attach ; 

__attribute__((used)) static int demod_attach_stv0367(struct ngene_channel *chan,
				struct i2c_adapter *i2c)
{
	struct device *pdev = &chan->dev->pci_dev->dev;

	chan->fe = dvb_attach(stv0367ddb_attach,
			      &ddb_stv0367_config[(chan->number & 1)], i2c);

	if (!chan->fe) {
		dev_err(pdev, "stv0367ddb_attach() failed!\n");
		return -ENODEV;
	}

	chan->fe->sec_priv = chan;
	chan->gate_ctrl = chan->fe->ops.i2c_gate_ctrl;
	chan->fe->ops.i2c_gate_ctrl = drxk_gate_ctrl;
	return 0;
}