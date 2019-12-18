#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct adapter {int dummy; } ;
struct TYPE_4__ {int TM_Trigger; } ;
struct TYPE_5__ {int SupportAbility; TYPE_1__ RFCalibrateInfo; struct adapter* Adapter; } ;
typedef  TYPE_2__* PDM_ODM_T ;

/* Variables and functions */
 int BIT16 ; 
 int BIT17 ; 
 int /*<<< orphan*/  ODM_RF_PATH_A ; 
 int ODM_RF_TX_PWR_TRACK ; 
 int /*<<< orphan*/  ODM_TXPowerTrackingCallback_ThermalMeter (struct adapter*) ; 
 int /*<<< orphan*/  PHY_SetRFReg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  RF_T_METER_NEW ; 

void ODM_TXPowerTrackingCheck(PDM_ODM_T pDM_Odm)
{
	struct adapter *Adapter = pDM_Odm->Adapter;

	if (!(pDM_Odm->SupportAbility & ODM_RF_TX_PWR_TRACK))
		return;

	if (!pDM_Odm->RFCalibrateInfo.TM_Trigger) { /* at least delay 1 sec */
		PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_T_METER_NEW, (BIT17 | BIT16), 0x03);

		/* DBG_871X("Trigger Thermal Meter!!\n"); */

		pDM_Odm->RFCalibrateInfo.TM_Trigger = 1;
		return;
	} else {
		/* DBG_871X("Schedule TxPowerTracking direct call!!\n"); */
		ODM_TXPowerTrackingCallback_ThermalMeter(Adapter);
		pDM_Odm->RFCalibrateInfo.TM_Trigger = 0;
	}
}