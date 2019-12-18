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
struct tc90522_config {int lpf; int /*<<< orphan*/  fe; int /*<<< orphan*/ * tuner_i2c; } ;
struct qm1d1c0042_config {int lpf; int /*<<< orphan*/  fe; int /*<<< orphan*/ * tuner_i2c; } ;
struct em28xx_dvb {int /*<<< orphan*/ * fe; void* i2c_client_demod; void* i2c_client_tuner; } ;
struct em28xx {size_t def_i2c_bus; int /*<<< orphan*/ * i2c_adap; struct em28xx_dvb* dvb; } ;

/* Variables and functions */
 int ENODEV ; 
 void* dvb_module_probe (char*,char*,int /*<<< orphan*/ *,int,struct tc90522_config*) ; 
 int /*<<< orphan*/  dvb_module_release (void*) ; 
 int /*<<< orphan*/  px_bcud_init (struct em28xx*) ; 

__attribute__((used)) static int em28178_dvb_init_plex_px_bcud(struct em28xx *dev)
{
	struct em28xx_dvb *dvb = dev->dvb;
	struct tc90522_config tc90522_config = {};
	struct qm1d1c0042_config qm1d1c0042_config = {};

	/* attach demod */
	dvb->i2c_client_demod = dvb_module_probe("tc90522", "tc90522sat",
						 &dev->i2c_adap[dev->def_i2c_bus],
						 0x15, &tc90522_config);
	if (!dvb->i2c_client_demod)
		return -ENODEV;

	/* attach tuner */
	qm1d1c0042_config.fe = tc90522_config.fe;
	qm1d1c0042_config.lpf = 1;

	dvb->i2c_client_tuner = dvb_module_probe("qm1d1c0042", NULL,
						 tc90522_config.tuner_i2c,
						 0x61, &qm1d1c0042_config);
	if (!dvb->i2c_client_tuner) {
		dvb_module_release(dvb->i2c_client_demod);
		return -ENODEV;
	}

	dvb->fe[0] = tc90522_config.fe;
	px_bcud_init(dev);

	return 0;
}