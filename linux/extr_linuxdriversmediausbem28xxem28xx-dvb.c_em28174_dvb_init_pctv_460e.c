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
struct tda10071_platform_data {int clk; int i2c_wr_max; int pll_multiplier; int tuner_i2c_addr; int /*<<< orphan*/  dvb_frontend; int /*<<< orphan*/  (* get_dvb_frontend ) (void*) ;int /*<<< orphan*/  ts_mode; } ;
struct em28xx_dvb {void* i2c_client_demod; void* i2c_client_sec; int /*<<< orphan*/ * fe; } ;
struct em28xx {size_t def_i2c_bus; int /*<<< orphan*/ * i2c_adap; struct em28xx_dvb* dvb; } ;
struct a8293_platform_data {int clk; int i2c_wr_max; int pll_multiplier; int tuner_i2c_addr; int /*<<< orphan*/  dvb_frontend; int /*<<< orphan*/  (* get_dvb_frontend ) (void*) ;int /*<<< orphan*/  ts_mode; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  TDA10071_TS_SERIAL ; 
 void* dvb_module_probe (char*,char*,int /*<<< orphan*/ *,int,struct tda10071_platform_data*) ; 
 int /*<<< orphan*/  dvb_module_release (void*) ; 
 int /*<<< orphan*/  stub1 (void*) ; 

__attribute__((used)) static int em28174_dvb_init_pctv_460e(struct em28xx *dev)
{
	struct em28xx_dvb *dvb = dev->dvb;
	struct tda10071_platform_data tda10071_pdata = {};
	struct a8293_platform_data a8293_pdata = {};

	/* attach demod + tuner combo */
	tda10071_pdata.clk = 40444000; /* 40.444 MHz */
	tda10071_pdata.i2c_wr_max = 64;
	tda10071_pdata.ts_mode = TDA10071_TS_SERIAL;
	tda10071_pdata.pll_multiplier = 20;
	tda10071_pdata.tuner_i2c_addr = 0x14;

	dvb->i2c_client_demod = dvb_module_probe("tda10071", "tda10071_cx24118",
						 &dev->i2c_adap[dev->def_i2c_bus],
						 0x55, &tda10071_pdata);
	if (!dvb->i2c_client_demod)
		return -ENODEV;

	dvb->fe[0] = tda10071_pdata.get_dvb_frontend(dvb->i2c_client_demod);

	/* attach SEC */
	a8293_pdata.dvb_frontend = dvb->fe[0];

	dvb->i2c_client_sec = dvb_module_probe("a8293", NULL,
					       &dev->i2c_adap[dev->def_i2c_bus],
					       0x08, &a8293_pdata);
	if (!dvb->i2c_client_sec) {
		dvb_module_release(dvb->i2c_client_demod);
		return -ENODEV;
	}

	return 0;
}