#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct i2c_adapter {int /*<<< orphan*/  name; } ;
struct mantis_pci {struct mantis_hwconfig* hwconfig; struct i2c_adapter adapter; } ;
struct mantis_hwconfig {int /*<<< orphan*/  reset; } ;
struct dvb_frontend {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MANTIS_ERROR ; 
 int /*<<< orphan*/  POWER_ON ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*,...) ; 
 struct dvb_frontend* dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct i2c_adapter*) ; 
 int /*<<< orphan*/  hopper_vp3028_config ; 
 int mantis_frontend_power (struct mantis_pci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mantis_gpio_set_bits (struct mantis_pci*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  zl10353_attach ; 

__attribute__((used)) static int vp3028_frontend_init(struct mantis_pci *mantis, struct dvb_frontend *fe)
{
	struct i2c_adapter *adapter	= &mantis->adapter;
	struct mantis_hwconfig *config	= mantis->hwconfig;
	int err = 0;

	mantis_gpio_set_bits(mantis, config->reset, 0);
	msleep(100);
	err = mantis_frontend_power(mantis, POWER_ON);
	msleep(100);
	mantis_gpio_set_bits(mantis, config->reset, 1);

	err = mantis_frontend_power(mantis, POWER_ON);
	if (err == 0) {
		msleep(250);
		dprintk(MANTIS_ERROR, 1, "Probing for 10353 (DVB-T)");
		fe = dvb_attach(zl10353_attach, &hopper_vp3028_config, adapter);

		if (!fe)
			return -1;
	} else {
		dprintk(MANTIS_ERROR, 1, "Frontend on <%s> POWER ON failed! <%d>",
			adapter->name,
			err);

		return -EIO;
	}
	dprintk(MANTIS_ERROR, 1, "Done!");

	return 0;
}