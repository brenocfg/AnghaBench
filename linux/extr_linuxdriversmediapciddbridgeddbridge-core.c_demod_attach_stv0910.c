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
struct stv0910_cfg {int single; int parallel; int tsspeed; int adr; } ;
struct lnbh25_config {int i2c_address; } ;
struct i2c_adapter {int dummy; } ;
struct device {int dummy; } ;
struct ddb_input {int nr; TYPE_3__* port; } ;
struct ddb_dvb {void* fe; } ;
struct TYPE_6__ {TYPE_2__* dev; struct ddb_dvb* dvb; TYPE_1__* i2c; } ;
struct TYPE_5__ {struct device* dev; } ;
struct TYPE_4__ {struct i2c_adapter adap; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 void* dvb_attach (int /*<<< orphan*/ ,void*,...) ; 
 int /*<<< orphan*/  dvb_frontend_detach (void*) ; 
 scalar_t__ has_lnbh25 (struct i2c_adapter*,int) ; 
 int /*<<< orphan*/  lnbh25_attach ; 
 struct lnbh25_config lnbh25_cfg ; 
 int /*<<< orphan*/  stv0910_attach ; 
 struct stv0910_cfg stv0910_p ; 
 scalar_t__ stv0910_single ; 

__attribute__((used)) static int demod_attach_stv0910(struct ddb_input *input, int type, int tsfast)
{
	struct i2c_adapter *i2c = &input->port->i2c->adap;
	struct ddb_dvb *dvb = &input->port->dvb[input->nr & 1];
	struct device *dev = input->port->dev->dev;
	struct stv0910_cfg cfg = stv0910_p;
	struct lnbh25_config lnbcfg = lnbh25_cfg;

	if (stv0910_single)
		cfg.single = 1;

	if (type)
		cfg.parallel = 2;

	if (tsfast) {
		dev_info(dev, "Enabling stv0910 higher speed TS\n");
		cfg.tsspeed = 0x10;
	}

	dvb->fe = dvb_attach(stv0910_attach, i2c, &cfg, (input->nr & 1));
	if (!dvb->fe) {
		cfg.adr = 0x6c;
		dvb->fe = dvb_attach(stv0910_attach, i2c,
				     &cfg, (input->nr & 1));
	}
	if (!dvb->fe) {
		dev_err(dev, "No STV0910 found!\n");
		return -ENODEV;
	}

	/* attach lnbh25 - leftshift by one as the lnbh25 driver expects 8bit
	 * i2c addresses
	 */
	if (has_lnbh25(i2c, 0x0d))
		lnbcfg.i2c_address = (((input->nr & 1) ? 0x0d : 0x0c) << 1);
	else
		lnbcfg.i2c_address = (((input->nr & 1) ? 0x09 : 0x08) << 1);

	if (!dvb_attach(lnbh25_attach, dvb->fe, &lnbcfg, i2c)) {
		dev_err(dev, "No LNBH25 found!\n");
		dvb_frontend_detach(dvb->fe);
		return -ENODEV;
	}

	return 0;
}