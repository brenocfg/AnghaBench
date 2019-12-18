#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct i2c_adapter {int /*<<< orphan*/  name; } ;
struct mantis_pci {struct dvb_frontend* fe; struct i2c_adapter adapter; } ;
struct dvb_frontend {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  demod_address; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MANTIS_ERROR ; 
 int /*<<< orphan*/  POWER_ON ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*,...) ; 
 struct dvb_frontend* dvb_attach (int /*<<< orphan*/ ,TYPE_1__*,struct i2c_adapter*) ; 
 int mantis_frontend_power (struct mantis_pci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mantis_frontend_soft_reset (struct mantis_pci*) ; 
 int /*<<< orphan*/  mb86a16_attach ; 
 int /*<<< orphan*/  msleep (int) ; 
 TYPE_1__ vp1034_mb86a16_config ; 

__attribute__((used)) static int vp1034_frontend_init(struct mantis_pci *mantis, struct dvb_frontend *fe)
{
	struct i2c_adapter *adapter	= &mantis->adapter;

	int err = 0;

	err = mantis_frontend_power(mantis, POWER_ON);
	if (err == 0) {
		mantis_frontend_soft_reset(mantis);
		msleep(250);

		dprintk(MANTIS_ERROR, 1, "Probing for MB86A16 (DVB-S/DSS)");
		fe = dvb_attach(mb86a16_attach, &vp1034_mb86a16_config, adapter);
		if (fe) {
			dprintk(MANTIS_ERROR, 1,
			"found MB86A16 DVB-S/DSS frontend @0x%02x",
			vp1034_mb86a16_config.demod_address);

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