#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct i2c_adapter {int dummy; } ;
struct dvb_usb_adapter {TYPE_1__* fe_adap; int /*<<< orphan*/  dev; struct dib0700_adapter_state* priv; } ;
struct dvb_frontend {int /*<<< orphan*/  dvb; } ;
struct dib0700_adapter_state {int /*<<< orphan*/  frontend_firmware; } ;
struct TYPE_2__ {struct dvb_frontend* fe; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_DVB_DIB9000 ; 
 int /*<<< orphan*/  DIBX000_I2C_INTERFACE_GPIO_1_2 ; 
 int ENODEV ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib0090_fw_register ; 
 scalar_t__ dib01x0_pmu_update (struct i2c_adapter*,int*,int) ; 
 int /*<<< orphan*/  dib0700_set_i2c_speed (int /*<<< orphan*/ ,int) ; 
 scalar_t__ dib9000_firmware_post_pll_init (struct dvb_frontend*) ; 
 int /*<<< orphan*/  dib9000_fw_set_component_bus_speed (struct dvb_frontend*,int) ; 
 struct i2c_adapter* dib9000_get_component_bus_interface (struct dvb_frontend*) ; 
 struct i2c_adapter* dib9000_get_i2c_master (struct dvb_frontend*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dvb_frontend* dib9000_get_slave_frontend (struct dvb_frontend*,int) ; 
 struct i2c_adapter* dib9000_get_tuner_interface (struct dvb_frontend*) ; 
 int /*<<< orphan*/  dib9000_set_i2c_adapter (struct dvb_frontend*,struct i2c_adapter*) ; 
 int /*<<< orphan*/ * dvb_attach (int /*<<< orphan*/ ,struct dvb_frontend*,struct i2c_adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nim9090md_dib0090_config ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nim9090md_tuner_attach(struct dvb_usb_adapter *adap)
{
	struct dib0700_adapter_state *state = adap->priv;
	struct i2c_adapter *i2c;
	struct dvb_frontend *fe_slave;
	u16 data_dib190[10] = {
		1, 0x5374,
		2, 0x01ae,
		7, 0x0020,
		0, 0x00ef,
		8, 0x0406,
	};
	if (!IS_ENABLED(CONFIG_DVB_DIB9000))
		return -ENODEV;
	i2c = dib9000_get_tuner_interface(adap->fe_adap[0].fe);
	if (dvb_attach(dib0090_fw_register, adap->fe_adap[0].fe, i2c, &nim9090md_dib0090_config[0]) == NULL)
		return -ENODEV;
	i2c = dib9000_get_i2c_master(adap->fe_adap[0].fe, DIBX000_I2C_INTERFACE_GPIO_1_2, 0);
	if (!i2c)
		return -ENODEV;
	if (dib01x0_pmu_update(i2c, data_dib190, 10) < 0)
		return -ENODEV;

	dib0700_set_i2c_speed(adap->dev, 1500);
	if (dib9000_firmware_post_pll_init(adap->fe_adap[0].fe) < 0)
		return -ENODEV;

	fe_slave = dib9000_get_slave_frontend(adap->fe_adap[0].fe, 1);
	if (fe_slave != NULL) {
		i2c = dib9000_get_component_bus_interface(adap->fe_adap[0].fe);
		dib9000_set_i2c_adapter(fe_slave, i2c);

		i2c = dib9000_get_tuner_interface(fe_slave);
		if (dvb_attach(dib0090_fw_register, fe_slave, i2c, &nim9090md_dib0090_config[1]) == NULL)
			return -ENODEV;
		fe_slave->dvb = adap->fe_adap[0].fe->dvb;
		dib9000_fw_set_component_bus_speed(adap->fe_adap[0].fe, 1500);
		if (dib9000_firmware_post_pll_init(fe_slave) < 0)
			return -ENODEV;
	}
	release_firmware(state->frontend_firmware);

	return 0;
}