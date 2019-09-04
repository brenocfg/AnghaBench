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
struct dm1105_dev {int boardnr; TYPE_3__* fe; int /*<<< orphan*/  dvb_adapter; TYPE_1__* pdev; int /*<<< orphan*/  i2c_adap; int /*<<< orphan*/  i2c_bb_adap; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* release ) (TYPE_3__*) ;void* set_voltage; } ;
struct TYPE_8__ {TYPE_2__ ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  DM1105_BOARD_AXESS_DM05 131 
#define  DM1105_BOARD_DVBWORLD_2002 130 
#define  DM1105_BOARD_DVBWORLD_2004 129 
#define  DM1105_BOARD_UNBRANDED_I2C_ON_GPIO 128 
 int /*<<< orphan*/  DVB_PLL_OPERA1 ; 
 int ENODEV ; 
 int /*<<< orphan*/  GPIO15 ; 
 int /*<<< orphan*/  cx24116_attach ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dm1105_gpio_clear (struct dm1105_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm1105_gpio_enable (struct dm1105_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dm1105_gpio_set (struct dm1105_dev*,int /*<<< orphan*/ ) ; 
 void* dm1105_set_voltage ; 
 int /*<<< orphan*/  ds3000_attach ; 
 void* dvb_attach (int /*<<< orphan*/ ,TYPE_3__*,int,...) ; 
 int /*<<< orphan*/  dvb_pll_attach ; 
 int dvb_register_frontend (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  dvbworld_ds3000_config ; 
 int /*<<< orphan*/  dvbworld_ts2020_config ; 
 int /*<<< orphan*/  earda_config ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  serit_config ; 
 int /*<<< orphan*/  serit_sp2633_config ; 
 int /*<<< orphan*/  sharp_z0194a_config ; 
 int /*<<< orphan*/  si21xx_attach ; 
 int /*<<< orphan*/  stb6000_attach ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stv0288_attach ; 
 int /*<<< orphan*/  stv0299_attach ; 
 int /*<<< orphan*/  ts2020_attach ; 

__attribute__((used)) static int frontend_init(struct dm1105_dev *dev)
{
	int ret;

	switch (dev->boardnr) {
	case DM1105_BOARD_UNBRANDED_I2C_ON_GPIO:
		dm1105_gpio_enable(dev, GPIO15, 1);
		dm1105_gpio_clear(dev, GPIO15);
		msleep(100);
		dm1105_gpio_set(dev, GPIO15);
		msleep(200);
		dev->fe = dvb_attach(
			stv0299_attach, &sharp_z0194a_config,
			&dev->i2c_bb_adap);
		if (dev->fe) {
			dev->fe->ops.set_voltage = dm1105_set_voltage;
			dvb_attach(dvb_pll_attach, dev->fe, 0x60,
					&dev->i2c_bb_adap, DVB_PLL_OPERA1);
			break;
		}

		dev->fe = dvb_attach(
			stv0288_attach, &earda_config,
			&dev->i2c_bb_adap);
		if (dev->fe) {
			dev->fe->ops.set_voltage = dm1105_set_voltage;
			dvb_attach(stb6000_attach, dev->fe, 0x61,
					&dev->i2c_bb_adap);
			break;
		}

		dev->fe = dvb_attach(
			si21xx_attach, &serit_config,
			&dev->i2c_bb_adap);
		if (dev->fe)
			dev->fe->ops.set_voltage = dm1105_set_voltage;
		break;
	case DM1105_BOARD_DVBWORLD_2004:
		dev->fe = dvb_attach(
			cx24116_attach, &serit_sp2633_config,
			&dev->i2c_adap);
		if (dev->fe) {
			dev->fe->ops.set_voltage = dm1105_set_voltage;
			break;
		}

		dev->fe = dvb_attach(
			ds3000_attach, &dvbworld_ds3000_config,
			&dev->i2c_adap);
		if (dev->fe) {
			dvb_attach(ts2020_attach, dev->fe,
				&dvbworld_ts2020_config, &dev->i2c_adap);
			dev->fe->ops.set_voltage = dm1105_set_voltage;
		}

		break;
	case DM1105_BOARD_DVBWORLD_2002:
	case DM1105_BOARD_AXESS_DM05:
	default:
		dev->fe = dvb_attach(
			stv0299_attach, &sharp_z0194a_config,
			&dev->i2c_adap);
		if (dev->fe) {
			dev->fe->ops.set_voltage = dm1105_set_voltage;
			dvb_attach(dvb_pll_attach, dev->fe, 0x60,
					&dev->i2c_adap, DVB_PLL_OPERA1);
			break;
		}

		dev->fe = dvb_attach(
			stv0288_attach, &earda_config,
			&dev->i2c_adap);
		if (dev->fe) {
			dev->fe->ops.set_voltage = dm1105_set_voltage;
			dvb_attach(stb6000_attach, dev->fe, 0x61,
					&dev->i2c_adap);
			break;
		}

		dev->fe = dvb_attach(
			si21xx_attach, &serit_config,
			&dev->i2c_adap);
		if (dev->fe)
			dev->fe->ops.set_voltage = dm1105_set_voltage;

	}

	if (!dev->fe) {
		dev_err(&dev->pdev->dev, "could not attach frontend\n");
		return -ENODEV;
	}

	ret = dvb_register_frontend(&dev->dvb_adapter, dev->fe);
	if (ret < 0) {
		if (dev->fe->ops.release)
			dev->fe->ops.release(dev->fe);
		dev->fe = NULL;
		return ret;
	}

	return 0;
}