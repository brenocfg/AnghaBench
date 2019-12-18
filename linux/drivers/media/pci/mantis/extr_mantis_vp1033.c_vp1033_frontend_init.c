#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct i2c_adapter {int /*<<< orphan*/  name; } ;
struct mantis_pci {struct dvb_frontend* fe; struct i2c_adapter adapter; } ;
struct TYPE_5__ {int /*<<< orphan*/  set_params; } ;
struct TYPE_6__ {TYPE_1__ tuner_ops; } ;
struct dvb_frontend {TYPE_2__ ops; } ;
struct TYPE_7__ {int /*<<< orphan*/  demod_address; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MANTIS_ERROR ; 
 int /*<<< orphan*/  POWER_ON ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*,...) ; 
 struct dvb_frontend* dvb_attach (int /*<<< orphan*/ ,TYPE_3__*,struct i2c_adapter*) ; 
 TYPE_3__ lgtdqcs001f_config ; 
 int /*<<< orphan*/  lgtdqcs001f_tuner_set ; 
 int mantis_frontend_power (struct mantis_pci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mantis_frontend_soft_reset (struct mantis_pci*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stv0299_attach ; 

__attribute__((used)) static int vp1033_frontend_init(struct mantis_pci *mantis, struct dvb_frontend *fe)
{
	struct i2c_adapter *adapter	= &mantis->adapter;

	int err = 0;

	err = mantis_frontend_power(mantis, POWER_ON);
	if (err == 0) {
		mantis_frontend_soft_reset(mantis);
		msleep(250);

		dprintk(MANTIS_ERROR, 1, "Probing for STV0299 (DVB-S)");
		fe = dvb_attach(stv0299_attach, &lgtdqcs001f_config, adapter);

		if (fe) {
			fe->ops.tuner_ops.set_params = lgtdqcs001f_tuner_set;
			dprintk(MANTIS_ERROR, 1, "found STV0299 DVB-S frontend @ 0x%02x",
				lgtdqcs001f_config.demod_address);

			dprintk(MANTIS_ERROR, 1, "Mantis DVB-S STV0299 frontend attach success");
		} else {
			return -1;
		}
	} else {
		dprintk(MANTIS_ERROR, 1, "Frontend on <%s> POWER ON failed! <%d>",
			adapter->name,
			err);

		return -EIO;
	}
	mantis->fe = fe;
	dprintk(MANTIS_ERROR, 1, "Done!");

	return 0;
}