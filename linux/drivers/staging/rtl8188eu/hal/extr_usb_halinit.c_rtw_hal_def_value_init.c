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
typedef  size_t u8 ;
struct pwrctrl_priv {int /*<<< orphan*/  bkeepfwalive; } ;
struct TYPE_3__ {int bIQKInitialized; scalar_t__* ThermalValue_HP; scalar_t__ ThermalValue_HP_index; scalar_t__ TM_Trigger; } ;
struct TYPE_4__ {TYPE_1__ RFCalibrateInfo; } ;
struct hal_data_8188e {int PGMaxGroup; TYPE_2__ odmpriv; scalar_t__ pwrGroupCnt; scalar_t__ LastHMEBoxNum; } ;
struct adapter {struct pwrctrl_priv pwrctrlpriv; struct hal_data_8188e* HalData; } ;

/* Variables and functions */
 size_t HP_THERMAL_NUM ; 

void rtw_hal_def_value_init(struct adapter *adapt)
{
	struct hal_data_8188e *haldata = adapt->HalData;
	struct pwrctrl_priv *pwrctrlpriv;
	u8 i;

	pwrctrlpriv = &adapt->pwrctrlpriv;

	/* init default value */
	if (!pwrctrlpriv->bkeepfwalive)
		haldata->LastHMEBoxNum = 0;

	/* init dm default value */
	haldata->odmpriv.RFCalibrateInfo.bIQKInitialized = false;
	haldata->odmpriv.RFCalibrateInfo.TM_Trigger = 0;/* for IQK */
	haldata->pwrGroupCnt = 0;
	haldata->PGMaxGroup = 13;
	haldata->odmpriv.RFCalibrateInfo.ThermalValue_HP_index = 0;
	for (i = 0; i < HP_THERMAL_NUM; i++)
		haldata->odmpriv.RFCalibrateInfo.ThermalValue_HP[i] = 0;
}