#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wm831x_pdata {struct wm831x_backup_pdata* backup; } ;
struct wm831x_backup_pdata {int vlim; int ilim; scalar_t__ no_constant_voltage; scalar_t__ charger_enable; } ;
struct wm831x {TYPE_1__* dev; } ;
struct TYPE_3__ {struct wm831x_pdata* platform_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM831X_BACKUP_CHARGER_CONTROL ; 
 int WM831X_BKUP_BATT_DET_ENA ; 
 int WM831X_BKUP_BATT_DET_ENA_MASK ; 
 int WM831X_BKUP_CHG_ENA ; 
 int WM831X_BKUP_CHG_ENA_MASK ; 
 int WM831X_BKUP_CHG_ILIM_MASK ; 
 int WM831X_BKUP_CHG_MODE ; 
 int WM831X_BKUP_CHG_MODE_MASK ; 
 int WM831X_BKUP_CHG_VLIM ; 
 int WM831X_BKUP_CHG_VLIM_MASK ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  wm831x_reg_lock (struct wm831x*) ; 
 int wm831x_reg_unlock (struct wm831x*) ; 
 int wm831x_set_bits (struct wm831x*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void wm831x_config_backup(struct wm831x *wm831x)
{
	struct wm831x_pdata *wm831x_pdata = wm831x->dev->platform_data;
	struct wm831x_backup_pdata *pdata;
	int ret, reg;

	if (!wm831x_pdata || !wm831x_pdata->backup) {
		dev_warn(wm831x->dev,
			 "No backup battery charger configuration\n");
		return;
	}

	pdata = wm831x_pdata->backup;

	reg = 0;

	if (pdata->charger_enable)
		reg |= WM831X_BKUP_CHG_ENA | WM831X_BKUP_BATT_DET_ENA;
	if (pdata->no_constant_voltage)
		reg |= WM831X_BKUP_CHG_MODE;

	switch (pdata->vlim) {
	case 2500:
		break;
	case 3100:
		reg |= WM831X_BKUP_CHG_VLIM;
		break;
	default:
		dev_err(wm831x->dev, "Invalid backup voltage limit %dmV\n",
			pdata->vlim);
	}

	switch (pdata->ilim) {
	case 100:
		break;
	case 200:
		reg |= 1;
		break;
	case 300:
		reg |= 2;
		break;
	case 400:
		reg |= 3;
		break;
	default:
		dev_err(wm831x->dev, "Invalid backup current limit %duA\n",
			pdata->ilim);
	}

	ret = wm831x_reg_unlock(wm831x);
	if (ret != 0) {
		dev_err(wm831x->dev, "Failed to unlock registers: %d\n", ret);
		return;
	}

	ret = wm831x_set_bits(wm831x, WM831X_BACKUP_CHARGER_CONTROL,
			      WM831X_BKUP_CHG_ENA_MASK |
			      WM831X_BKUP_CHG_MODE_MASK |
			      WM831X_BKUP_BATT_DET_ENA_MASK |
			      WM831X_BKUP_CHG_VLIM_MASK |
			      WM831X_BKUP_CHG_ILIM_MASK,
			      reg);
	if (ret != 0)
		dev_err(wm831x->dev,
			"Failed to set backup charger config: %d\n", ret);

	wm831x_reg_lock(wm831x);
}