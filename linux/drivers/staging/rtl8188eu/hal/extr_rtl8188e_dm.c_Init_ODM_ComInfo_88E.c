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
struct odm_dm_struct {int bIsMPChip; int BbSwingIdxOfdm; int BbSwingIdxOfdmCurrent; int BbSwingFlagOfdm; int SupportAbility; int /*<<< orphan*/  AntDivType; int /*<<< orphan*/  bWIFITest; int /*<<< orphan*/  PatchID; int /*<<< orphan*/  CutVersion; int /*<<< orphan*/  SupportICType; int /*<<< orphan*/  SupportPlatform; struct adapter* Adapter; } ;
struct TYPE_3__ {scalar_t__ ChipType; } ;
struct dm_priv {int InitODMFlag; } ;
struct hal_data_8188e {int /*<<< orphan*/  TRxAntDivType; int /*<<< orphan*/  CustomerID; TYPE_1__ VersionID; struct odm_dm_struct odmpriv; struct dm_priv dmpriv; } ;
struct TYPE_4__ {int /*<<< orphan*/  wifi_spec; } ;
struct adapter {TYPE_2__ registrypriv; struct hal_data_8188e* HalData; } ;

/* Variables and functions */
 scalar_t__ NORMAL_CHIP ; 
 int /*<<< orphan*/  ODM_CE ; 
 int /*<<< orphan*/  ODM_CUT_A ; 
 int ODM_RF_CALIBRATION ; 
 int ODM_RF_TX_PWR_TRACK ; 
 int /*<<< orphan*/  ODM_RTL8188E ; 
 int /*<<< orphan*/  memset (struct odm_dm_struct*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void Init_ODM_ComInfo_88E(struct adapter *Adapter)
{
	struct hal_data_8188e *hal_data = Adapter->HalData;
	struct dm_priv	*pdmpriv = &hal_data->dmpriv;
	struct odm_dm_struct *dm_odm = &(hal_data->odmpriv);

	/*  Init Value */
	memset(dm_odm, 0, sizeof(*dm_odm));

	dm_odm->Adapter = Adapter;
	dm_odm->SupportPlatform = ODM_CE;
	dm_odm->SupportICType = ODM_RTL8188E;
	dm_odm->CutVersion = ODM_CUT_A;
	dm_odm->bIsMPChip = hal_data->VersionID.ChipType == NORMAL_CHIP;
	dm_odm->PatchID = hal_data->CustomerID;
	dm_odm->bWIFITest = Adapter->registrypriv.wifi_spec;

	dm_odm->AntDivType = hal_data->TRxAntDivType;

	/*  Tx power tracking BB swing table. */
	/*  The base index = 12. +((12-n)/2)dB 13~?? = decrease tx pwr by -((n-12)/2)dB */
	dm_odm->BbSwingIdxOfdm = 12; /*  Set defalut value as index 12. */
	dm_odm->BbSwingIdxOfdmCurrent = 12;
	dm_odm->BbSwingFlagOfdm = false;

	pdmpriv->InitODMFlag =	ODM_RF_CALIBRATION |
				ODM_RF_TX_PWR_TRACK;

	dm_odm->SupportAbility = pdmpriv->InitODMFlag;
}