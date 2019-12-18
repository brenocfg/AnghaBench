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
struct mt7601u_dev {int raw_temp; int curr_temp; int dpd_temp; int pll_lock_protect; int /*<<< orphan*/  dev; TYPE_1__* ee; } ;
struct TYPE_2__ {int ref_temp; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCU_CAL_DPD ; 
 int MT_EE_TEMPERATURE_SLOPE ; 
 int /*<<< orphan*/  MT_TEMP_MODE_HIGH ; 
 int /*<<< orphan*/  MT_TEMP_MODE_LOW ; 
 int /*<<< orphan*/  MT_TEMP_MODE_NORMAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int mt7601u_bbp_temp (struct mt7601u_dev*,int /*<<< orphan*/ ,char*) ; 
 int mt7601u_mcu_calibrate (struct mt7601u_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt7601u_rf_clear (struct mt7601u_dev*,int,int,int) ; 
 int /*<<< orphan*/  mt7601u_rf_rmw (struct mt7601u_dev*,int,int,int,int) ; 
 int /*<<< orphan*/  mt7601u_rf_wr (struct mt7601u_dev*,int,int,int) ; 
 int /*<<< orphan*/  mt7601u_vco_cal (struct mt7601u_dev*) ; 

__attribute__((used)) static int mt7601u_temp_comp(struct mt7601u_dev *dev, bool on)
{
	int ret, temp, hi_temp = 400, lo_temp = -200;

	temp = (dev->raw_temp - dev->ee->ref_temp) * MT_EE_TEMPERATURE_SLOPE;
	dev->curr_temp = temp;

	/* DPD Calibration */
	if (temp - dev->dpd_temp > 450 || temp - dev->dpd_temp < -450) {
		dev->dpd_temp = temp;

		ret = mt7601u_mcu_calibrate(dev, MCU_CAL_DPD, dev->dpd_temp);
		if (ret)
			return ret;

		mt7601u_vco_cal(dev);

		dev_dbg(dev->dev, "Recalibrate DPD\n");
	}

	/* PLL Lock Protect */
	if (temp < -50 && !dev->pll_lock_protect) { /* < 20C */
		dev->pll_lock_protect =  true;

		mt7601u_rf_wr(dev, 4, 4, 6);
		mt7601u_rf_clear(dev, 4, 10, 0x30);

		dev_dbg(dev->dev, "PLL lock protect on - too cold\n");
	} else if (temp > 50 && dev->pll_lock_protect) { /* > 30C */
		dev->pll_lock_protect = false;

		mt7601u_rf_wr(dev, 4, 4, 0);
		mt7601u_rf_rmw(dev, 4, 10, 0x30, 0x10);

		dev_dbg(dev->dev, "PLL lock protect off\n");
	}

	if (on) {
		hi_temp -= 50;
		lo_temp -= 50;
	}

	/* BBP CR for H, L, N temperature */
	if (temp > hi_temp)
		return mt7601u_bbp_temp(dev, MT_TEMP_MODE_HIGH, "high");
	else if (temp > lo_temp)
		return mt7601u_bbp_temp(dev, MT_TEMP_MODE_NORMAL, "normal");
	else
		return mt7601u_bbp_temp(dev, MT_TEMP_MODE_LOW, "low");
}