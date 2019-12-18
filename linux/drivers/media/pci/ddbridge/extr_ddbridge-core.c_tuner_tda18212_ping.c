#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  tda_id ;
struct i2c_adapter {int dummy; } ;
struct device {int dummy; } ;
struct ddb_input {int nr; TYPE_3__* port; } ;
struct ddb_dvb {TYPE_5__* fe; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (TYPE_5__*,int) ;} ;
struct TYPE_11__ {TYPE_4__ ops; } ;
struct TYPE_9__ {TYPE_2__* dev; struct ddb_dvb* dvb; TYPE_1__* i2c; } ;
struct TYPE_8__ {struct device* dev; } ;
struct TYPE_7__ {struct i2c_adapter adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 scalar_t__ i2c_read_regs (struct i2c_adapter*,unsigned short,int,int*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,int) ; 

__attribute__((used)) static int tuner_tda18212_ping(struct ddb_input *input, unsigned short adr)
{
	struct i2c_adapter *adapter = &input->port->i2c->adap;
	struct ddb_dvb *dvb = &input->port->dvb[input->nr & 1];
	struct device *dev = input->port->dev->dev;
	u8 tda_id[2];
	u8 subaddr = 0x00;

	dev_dbg(dev, "stv0367-tda18212 tuner ping\n");
	if (dvb->fe->ops.i2c_gate_ctrl)
		dvb->fe->ops.i2c_gate_ctrl(dvb->fe, 1);

	if (i2c_read_regs(adapter, adr, subaddr, tda_id, sizeof(tda_id)) < 0)
		dev_dbg(dev, "tda18212 ping 1 fail\n");
	if (i2c_read_regs(adapter, adr, subaddr, tda_id, sizeof(tda_id)) < 0)
		dev_warn(dev, "tda18212 ping failed, expect problems\n");

	if (dvb->fe->ops.i2c_gate_ctrl)
		dvb->fe->ops.i2c_gate_ctrl(dvb->fe, 0);

	return 0;
}