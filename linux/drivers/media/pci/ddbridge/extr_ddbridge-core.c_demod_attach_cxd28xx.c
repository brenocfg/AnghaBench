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
struct cxd2841er_config {int i2c_addr; int flags; int /*<<< orphan*/  xtal; } ;
struct TYPE_9__ {int /*<<< orphan*/  i2c_gate_ctrl; } ;
struct TYPE_10__ {TYPE_4__ ops; struct ddb_input* sec_priv; } ;
struct TYPE_8__ {TYPE_2__* dev; struct ddb_dvb* dvb; TYPE_1__* i2c; } ;
struct TYPE_7__ {struct device* dev; } ;
struct TYPE_6__ {struct i2c_adapter adap; } ;

/* Variables and functions */
 int CXD2841ER_AUTO_IFHZ ; 
 int CXD2841ER_EARLY_TUNE ; 
 int CXD2841ER_NO_AGCNEG ; 
 int CXD2841ER_NO_WAIT_LOCK ; 
 int CXD2841ER_TSBITS ; 
 int CXD2841ER_TS_SERIAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  SONY_XTAL_20500 ; 
 int /*<<< orphan*/  SONY_XTAL_24000 ; 
 int /*<<< orphan*/  cxd2841er_attach_t_c ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 TYPE_5__* dvb_attach (int /*<<< orphan*/ ,struct cxd2841er_config*,struct i2c_adapter*) ; 
 int /*<<< orphan*/  locked_gate_ctrl ; 

__attribute__((used)) static int demod_attach_cxd28xx(struct ddb_input *input, int par, int osc24)
{
	struct i2c_adapter *i2c = &input->port->i2c->adap;
	struct ddb_dvb *dvb = &input->port->dvb[input->nr & 1];
	struct device *dev = input->port->dev->dev;
	struct cxd2841er_config cfg;

	/* the cxd2841er driver expects 8bit/shifted I2C addresses */
	cfg.i2c_addr = ((input->nr & 1) ? 0x6d : 0x6c) << 1;

	cfg.xtal = osc24 ? SONY_XTAL_24000 : SONY_XTAL_20500;
	cfg.flags = CXD2841ER_AUTO_IFHZ | CXD2841ER_EARLY_TUNE |
		CXD2841ER_NO_WAIT_LOCK | CXD2841ER_NO_AGCNEG |
		CXD2841ER_TSBITS;

	if (!par)
		cfg.flags |= CXD2841ER_TS_SERIAL;

	/* attach frontend */
	dvb->fe = dvb_attach(cxd2841er_attach_t_c, &cfg, i2c);

	if (!dvb->fe) {
		dev_err(dev, "No cxd2837/38/43/54 found!\n");
		return -ENODEV;
	}
	dvb->fe->sec_priv = input;
	dvb->i2c_gate_ctrl = dvb->fe->ops.i2c_gate_ctrl;
	dvb->fe->ops.i2c_gate_ctrl = locked_gate_ctrl;
	return 0;
}