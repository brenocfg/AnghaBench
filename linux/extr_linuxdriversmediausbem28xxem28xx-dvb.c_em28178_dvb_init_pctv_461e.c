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
struct ts2020_config {int clk; int i2c_wr_max; int ts_clk; int ts_clk_pol; int agc; TYPE_3__* dvb_frontend; TYPE_3__* fe; struct i2c_adapter* (* get_i2c_adapter ) (void*) ;TYPE_3__* (* get_dvb_frontend ) (void*) ;int /*<<< orphan*/  ts_mode; } ;
struct m88ds3103_platform_data {int clk; int i2c_wr_max; int ts_clk; int ts_clk_pol; int agc; TYPE_3__* dvb_frontend; TYPE_3__* fe; struct i2c_adapter* (* get_i2c_adapter ) (void*) ;TYPE_3__* (* get_dvb_frontend ) (void*) ;int /*<<< orphan*/  ts_mode; } ;
struct i2c_adapter {int dummy; } ;
struct em28xx_dvb {void* i2c_client_demod; void* i2c_client_tuner; void* i2c_client_sec; TYPE_3__** fe; } ;
struct em28xx {size_t def_i2c_bus; struct i2c_adapter* i2c_adap; struct em28xx_dvb* dvb; } ;
struct a8293_platform_data {int clk; int i2c_wr_max; int ts_clk; int ts_clk_pol; int agc; TYPE_3__* dvb_frontend; TYPE_3__* fe; struct i2c_adapter* (* get_i2c_adapter ) (void*) ;TYPE_3__* (* get_dvb_frontend ) (void*) ;int /*<<< orphan*/  ts_mode; } ;
struct TYPE_4__ {int /*<<< orphan*/  get_rf_strength; } ;
struct TYPE_5__ {TYPE_1__ tuner_ops; int /*<<< orphan*/  read_signal_strength; } ;
struct TYPE_6__ {TYPE_2__ ops; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  M88DS3103_TS_PARALLEL ; 
 void* dvb_module_probe (char*,char*,struct i2c_adapter*,int,struct ts2020_config*) ; 
 int /*<<< orphan*/  dvb_module_release (void*) ; 
 TYPE_3__* stub1 (void*) ; 
 struct i2c_adapter* stub2 (void*) ; 

__attribute__((used)) static int em28178_dvb_init_pctv_461e(struct em28xx *dev)
{
	struct em28xx_dvb *dvb = dev->dvb;
	struct i2c_adapter *i2c_adapter;
	struct m88ds3103_platform_data m88ds3103_pdata = {};
	struct ts2020_config ts2020_config = {};
	struct a8293_platform_data a8293_pdata = {};

	/* attach demod */
	m88ds3103_pdata.clk = 27000000;
	m88ds3103_pdata.i2c_wr_max = 33;
	m88ds3103_pdata.ts_mode = M88DS3103_TS_PARALLEL;
	m88ds3103_pdata.ts_clk = 16000;
	m88ds3103_pdata.ts_clk_pol = 1;
	m88ds3103_pdata.agc = 0x99;

	dvb->i2c_client_demod = dvb_module_probe("m88ds3103", NULL,
						 &dev->i2c_adap[dev->def_i2c_bus],
						 0x68, &m88ds3103_pdata);
	if (!dvb->i2c_client_demod)
		return -ENODEV;

	dvb->fe[0] = m88ds3103_pdata.get_dvb_frontend(dvb->i2c_client_demod);
	i2c_adapter = m88ds3103_pdata.get_i2c_adapter(dvb->i2c_client_demod);

	/* attach tuner */
	ts2020_config.fe = dvb->fe[0];

	dvb->i2c_client_tuner = dvb_module_probe("ts2020", "ts2022",
						 i2c_adapter,
						 0x60, &ts2020_config);
	if (!dvb->i2c_client_tuner) {
		dvb_module_release(dvb->i2c_client_demod);
		return -ENODEV;
	}

	/* delegate signal strength measurement to tuner */
	dvb->fe[0]->ops.read_signal_strength =
			dvb->fe[0]->ops.tuner_ops.get_rf_strength;

	/* attach SEC */
	a8293_pdata.dvb_frontend = dvb->fe[0];
	dvb->i2c_client_sec = dvb_module_probe("a8293", NULL,
					       &dev->i2c_adap[dev->def_i2c_bus],
					       0x08, &a8293_pdata);
	if (!dvb->i2c_client_sec) {
		dvb_module_release(dvb->i2c_client_tuner);
		dvb_module_release(dvb->i2c_client_demod);
		return -ENODEV;
	}

	return 0;
}