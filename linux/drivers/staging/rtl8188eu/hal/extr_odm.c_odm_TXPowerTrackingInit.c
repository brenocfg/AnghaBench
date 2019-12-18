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
struct TYPE_2__ {int bTXPowerTracking; int TxPowerTrackControl; scalar_t__ TXPowercount; } ;
struct odm_dm_struct {int* mp_mode; TYPE_1__ RFCalibrateInfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_88E (char*,int) ; 

void odm_TXPowerTrackingInit(struct odm_dm_struct *pDM_Odm)
{
	pDM_Odm->RFCalibrateInfo.bTXPowerTracking = true;
	pDM_Odm->RFCalibrateInfo.TXPowercount = 0;
	if (*(pDM_Odm->mp_mode) != 1)
		pDM_Odm->RFCalibrateInfo.TxPowerTrackControl = true;
	MSG_88E("pDM_Odm TxPowerTrackControl = %d\n", pDM_Odm->RFCalibrateInfo.TxPowerTrackControl);

	pDM_Odm->RFCalibrateInfo.TxPowerTrackControl = true;
}