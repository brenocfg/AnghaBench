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
struct mxl5xx_cfg {struct ddb_link* fw_priv; } ;
struct i2c_adapter {int dummy; } ;
struct ddb_port {size_t lnr; struct ddb_dvb* dvb; TYPE_1__* i2c; struct ddb* dev; } ;
struct ddb_link {int dummy; } ;
struct ddb_input {int nr; struct ddb_port* port; } ;
struct ddb_dvb {int input; TYPE_3__* fe; int /*<<< orphan*/  diseqc_send_master_cmd; int /*<<< orphan*/ * set_input; } ;
struct ddb {int /*<<< orphan*/  dev; struct ddb_link* link; } ;
struct TYPE_5__ {int /*<<< orphan*/  diseqc_send_burst; int /*<<< orphan*/  diseqc_send_master_cmd; int /*<<< orphan*/  set_tone; int /*<<< orphan*/  enable_high_lnb_voltage; int /*<<< orphan*/  set_voltage; } ;
struct TYPE_6__ {struct ddb_input* sec_priv; TYPE_2__ ops; } ;
struct TYPE_4__ {struct i2c_adapter adap; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  LNB_CMD_INIT ; 
 int /*<<< orphan*/  SEC_VOLTAGE_OFF ; 
 int /*<<< orphan*/  ddb_lnb_init_fmode (struct ddb*,struct ddb_link*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* dvb_attach (int /*<<< orphan*/ ,struct i2c_adapter*,struct mxl5xx_cfg*,int,int,int /*<<< orphan*/ **) ; 
 int fmode ; 
 int /*<<< orphan*/  lnb_command (struct ddb*,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lnb_set_voltage (struct ddb*,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max_enable_high_lnb_voltage ; 
 int /*<<< orphan*/  max_send_burst ; 
 int /*<<< orphan*/  max_send_master_cmd ; 
 int /*<<< orphan*/  max_set_tone ; 
 int /*<<< orphan*/  max_set_voltage ; 
 struct mxl5xx_cfg mxl5xx ; 
 int /*<<< orphan*/  mxl5xx_attach ; 

int ddb_fe_attach_mxl5xx(struct ddb_input *input)
{
	struct ddb *dev = input->port->dev;
	struct i2c_adapter *i2c = &input->port->i2c->adap;
	struct ddb_dvb *dvb = &input->port->dvb[input->nr & 1];
	struct ddb_port *port = input->port;
	struct ddb_link *link = &dev->link[port->lnr];
	struct mxl5xx_cfg cfg;
	int demod, tuner;

	cfg = mxl5xx;
	cfg.fw_priv = link;
	dvb->set_input = NULL;

	demod = input->nr;
	tuner = demod & 3;
	if (fmode == 3)
		tuner = 0;

	dvb->fe = dvb_attach(mxl5xx_attach, i2c, &cfg,
			     demod, tuner, &dvb->set_input);

	if (!dvb->fe) {
		dev_err(dev->dev, "No MXL5XX found!\n");
		return -ENODEV;
	}

	if (!dvb->set_input) {
		dev_err(dev->dev, "No mxl5xx_set_input function pointer!\n");
		return -ENODEV;
	}

	if (input->nr < 4) {
		lnb_command(dev, port->lnr, input->nr, LNB_CMD_INIT);
		lnb_set_voltage(dev, port->lnr, input->nr, SEC_VOLTAGE_OFF);
	}
	ddb_lnb_init_fmode(dev, link, fmode);

	dvb->fe->ops.set_voltage = max_set_voltage;
	dvb->fe->ops.enable_high_lnb_voltage = max_enable_high_lnb_voltage;
	dvb->fe->ops.set_tone = max_set_tone;
	dvb->diseqc_send_master_cmd = dvb->fe->ops.diseqc_send_master_cmd;
	dvb->fe->ops.diseqc_send_master_cmd = max_send_master_cmd;
	dvb->fe->ops.diseqc_send_burst = max_send_burst;
	dvb->fe->sec_priv = input;
	dvb->input = tuner;
	return 0;
}