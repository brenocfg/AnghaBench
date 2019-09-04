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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct tda18212_config {int if_dvbt_6; int if_dvbt_7; int if_dvbt_8; int if_dvbt2_6; int if_dvbt2_7; int if_dvbt2_8; int if_dvbc; int /*<<< orphan*/  fe; } ;
struct i2c_client {int dummy; } ;
struct i2c_adapter {int dummy; } ;
struct device {int dummy; } ;
struct ddb_input {int nr; TYPE_3__* port; } ;
struct ddb_dvb {struct i2c_client** i2c_client; int /*<<< orphan*/  fe; } ;
struct TYPE_6__ {TYPE_2__* dev; struct ddb_dvb* dvb; TYPE_1__* i2c; } ;
struct TYPE_5__ {struct device* dev; } ;
struct TYPE_4__ {struct i2c_adapter adap; } ;

/* Variables and functions */
 scalar_t__ DDB_TUNER_DVBCT_ST ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct i2c_client* dvb_module_probe (char*,int /*<<< orphan*/ *,struct i2c_adapter*,int,struct tda18212_config*) ; 
 int /*<<< orphan*/  tuner_tda18212_ping (struct ddb_input*,int) ; 

__attribute__((used)) static int tuner_attach_tda18212(struct ddb_input *input, u32 porttype)
{
	struct i2c_adapter *adapter = &input->port->i2c->adap;
	struct ddb_dvb *dvb = &input->port->dvb[input->nr & 1];
	struct device *dev = input->port->dev->dev;
	struct i2c_client *client;
	struct tda18212_config config = {
		.fe = dvb->fe,
		.if_dvbt_6 = 3550,
		.if_dvbt_7 = 3700,
		.if_dvbt_8 = 4150,
		.if_dvbt2_6 = 3250,
		.if_dvbt2_7 = 4000,
		.if_dvbt2_8 = 4000,
		.if_dvbc = 5000,
	};
	u8 addr = (input->nr & 1) ? 0x63 : 0x60;

	/* due to a hardware quirk with the I2C gate on the stv0367+tda18212
	 * combo, the tda18212 must be probed by reading it's id _twice_ when
	 * cold started, or it very likely will fail.
	 */
	if (porttype == DDB_TUNER_DVBCT_ST)
		tuner_tda18212_ping(input, addr);

	/* perform tuner probe/init/attach */
	client = dvb_module_probe("tda18212", NULL, adapter, addr, &config);
	if (!client)
		goto err;

	dvb->i2c_client[0] = client;
	return 0;
err:
	dev_err(dev, "TDA18212 tuner not found. Device is not fully operational.\n");
	return -ENODEV;
}