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
struct ts2020_config {TYPE_3__* fe; } ;
struct smi_port {scalar_t__ idx; TYPE_3__* fe; struct i2c_client* i2c_client_tuner; struct smi_dev* dev; } ;
struct smi_dev {struct i2c_adapter* i2c_bus; } ;
struct i2c_client {int dummy; } ;
struct i2c_board_info {int addr; struct ts2020_config* platform_data; int /*<<< orphan*/  type; } ;
struct i2c_adapter {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  get_rf_strength; } ;
struct TYPE_6__ {TYPE_1__ tuner_ops; int /*<<< orphan*/  read_signal_strength; } ;
struct TYPE_7__ {TYPE_2__ ops; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 TYPE_3__* dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct i2c_adapter*,struct i2c_adapter**) ; 
 int /*<<< orphan*/  dvb_frontend_detach (TYPE_3__*) ; 
 int /*<<< orphan*/  m88ds3103_attach ; 
 int /*<<< orphan*/  memset (struct i2c_board_info*,int /*<<< orphan*/ ,int) ; 
 struct i2c_client* smi_add_i2c_client (struct i2c_adapter*,struct i2c_board_info*) ; 
 int /*<<< orphan*/  smi_dvbsky_m88ds3103_cfg ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smi_dvbsky_m88ds3103_fe_attach(struct smi_port *port)
{
	int ret = 0;
	struct smi_dev *dev = port->dev;
	struct i2c_adapter *i2c;
	/* tuner I2C module */
	struct i2c_adapter *tuner_i2c_adapter;
	struct i2c_client *tuner_client;
	struct i2c_board_info tuner_info;
	struct ts2020_config ts2020_config = {};
	memset(&tuner_info, 0, sizeof(struct i2c_board_info));
	i2c = (port->idx == 0) ? &dev->i2c_bus[0] : &dev->i2c_bus[1];

	/* attach demod */
	port->fe = dvb_attach(m88ds3103_attach,
			&smi_dvbsky_m88ds3103_cfg, i2c, &tuner_i2c_adapter);
	if (!port->fe) {
		ret = -ENODEV;
		return ret;
	}
	/* attach tuner */
	ts2020_config.fe = port->fe;
	strscpy(tuner_info.type, "ts2020", I2C_NAME_SIZE);
	tuner_info.addr = 0x60;
	tuner_info.platform_data = &ts2020_config;
	tuner_client = smi_add_i2c_client(tuner_i2c_adapter, &tuner_info);
	if (!tuner_client) {
		ret = -ENODEV;
		goto err_tuner_i2c_device;
	}

	/* delegate signal strength measurement to tuner */
	port->fe->ops.read_signal_strength =
			port->fe->ops.tuner_ops.get_rf_strength;

	port->i2c_client_tuner = tuner_client;
	return ret;

err_tuner_i2c_device:
	dvb_frontend_detach(port->fe);
	return ret;
}