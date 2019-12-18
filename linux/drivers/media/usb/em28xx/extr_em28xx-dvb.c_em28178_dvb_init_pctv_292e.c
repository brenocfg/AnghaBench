#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct si2168_config {int spectral_inversion; int if_port; int /*<<< orphan*/  mdev; TYPE_2__* fe; int /*<<< orphan*/  ts_mode; struct i2c_adapter** i2c_adapter; } ;
struct si2157_config {int spectral_inversion; int if_port; int /*<<< orphan*/  mdev; TYPE_2__* fe; int /*<<< orphan*/  ts_mode; struct i2c_adapter** i2c_adapter; } ;
struct i2c_adapter {int dummy; } ;
struct em28xx_dvb {TYPE_2__** fe; void* i2c_client_demod; void* i2c_client_tuner; } ;
struct em28xx {size_t def_i2c_bus; int /*<<< orphan*/  media_dev; struct i2c_adapter* i2c_adap; struct em28xx_dvb* dvb; } ;
struct TYPE_3__ {int /*<<< orphan*/  set_lna; } ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  SI2168_TS_PARALLEL ; 
 void* dvb_module_probe (char*,int /*<<< orphan*/ *,struct i2c_adapter*,int,struct si2168_config*) ; 
 int /*<<< orphan*/  dvb_module_release (void*) ; 
 int /*<<< orphan*/  em28xx_pctv_292e_set_lna ; 

__attribute__((used)) static int em28178_dvb_init_pctv_292e(struct em28xx *dev)
{
	struct em28xx_dvb *dvb = dev->dvb;
	struct i2c_adapter *adapter;
	struct si2168_config si2168_config = {};
	struct si2157_config si2157_config = {};

	/* attach demod */
	si2168_config.i2c_adapter = &adapter;
	si2168_config.fe = &dvb->fe[0];
	si2168_config.ts_mode = SI2168_TS_PARALLEL;
	si2168_config.spectral_inversion = true;

	dvb->i2c_client_demod = dvb_module_probe("si2168", NULL,
						 &dev->i2c_adap[dev->def_i2c_bus],
						 0x64, &si2168_config);
	if (!dvb->i2c_client_demod)
		return -ENODEV;

	/* attach tuner */
	si2157_config.fe = dvb->fe[0];
	si2157_config.if_port = 1;
#ifdef CONFIG_MEDIA_CONTROLLER_DVB
	si2157_config.mdev = dev->media_dev;
#endif
	dvb->i2c_client_tuner = dvb_module_probe("si2157", NULL,
						 adapter,
						 0x60, &si2157_config);
	if (!dvb->i2c_client_tuner) {
		dvb_module_release(dvb->i2c_client_demod);
		return -ENODEV;
	}
	dvb->fe[0]->ops.set_lna = em28xx_pctv_292e_set_lna;

	return 0;
}