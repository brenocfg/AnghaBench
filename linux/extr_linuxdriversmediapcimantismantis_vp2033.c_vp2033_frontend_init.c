#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct i2c_adapter {int /*<<< orphan*/  name; } ;
struct mantis_pci {struct dvb_frontend* fe; struct i2c_adapter adapter; } ;
struct TYPE_6__ {int /*<<< orphan*/  set_params; } ;
struct TYPE_7__ {TYPE_1__ tuner_ops; } ;
struct dvb_frontend {TYPE_2__ ops; } ;
struct TYPE_8__ {int /*<<< orphan*/  demod_address; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MANTIS_DEBUG ; 
 int /*<<< orphan*/  MANTIS_ERROR ; 
 int /*<<< orphan*/  POWER_ON ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*,...) ; 
 struct dvb_frontend* dvb_attach (int /*<<< orphan*/ ,TYPE_3__*,struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int mantis_frontend_power (struct mantis_pci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mantis_frontend_soft_reset (struct mantis_pci*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  read_pwm (struct mantis_pci*) ; 
 int /*<<< orphan*/  tda10021_attach ; 
 int /*<<< orphan*/  tda10023_attach ; 
 int /*<<< orphan*/  tda1002x_cu1216_tuner_set ; 
 TYPE_3__ vp2033_tda10023_cu1216_config ; 
 TYPE_3__ vp2033_tda1002x_cu1216_config ; 

__attribute__((used)) static int vp2033_frontend_init(struct mantis_pci *mantis, struct dvb_frontend *fe)
{
	struct i2c_adapter *adapter = &mantis->adapter;

	int err = 0;

	err = mantis_frontend_power(mantis, POWER_ON);
	if (err == 0) {
		mantis_frontend_soft_reset(mantis);
		msleep(250);

		dprintk(MANTIS_ERROR, 1, "Probing for CU1216 (DVB-C)");
		fe = dvb_attach(tda10021_attach, &vp2033_tda1002x_cu1216_config,
				     adapter,
				     read_pwm(mantis));

		if (fe) {
			dprintk(MANTIS_ERROR, 1,
				"found Philips CU1216 DVB-C frontend (TDA10021) @ 0x%02x",
				vp2033_tda1002x_cu1216_config.demod_address);
		} else {
			fe = dvb_attach(tda10023_attach, &vp2033_tda10023_cu1216_config,
					     adapter,
					     read_pwm(mantis));

			if (fe) {
				dprintk(MANTIS_ERROR, 1,
					"found Philips CU1216 DVB-C frontend (TDA10023) @ 0x%02x",
					vp2033_tda1002x_cu1216_config.demod_address);
			}
		}

		if (fe) {
			fe->ops.tuner_ops.set_params = tda1002x_cu1216_tuner_set;
			dprintk(MANTIS_ERROR, 1, "Mantis DVB-C Philips CU1216 frontend attach success");
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
	dprintk(MANTIS_DEBUG, 1, "Done!");

	return 0;
}