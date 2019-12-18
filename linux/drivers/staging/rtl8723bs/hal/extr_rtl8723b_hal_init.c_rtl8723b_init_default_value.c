#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct TYPE_5__ {int /*<<< orphan*/  fakeBTEfuseModifiedMap; int /*<<< orphan*/  fakeBTEfuseInitMap; int /*<<< orphan*/  fakeBTEfuseContent; scalar_t__ fakeBTEfuseUsedBytes; int /*<<< orphan*/  BTEfuseModifiedMap; int /*<<< orphan*/  BTEfuseInitMap; int /*<<< orphan*/  BTEfuseContent; scalar_t__ BTEfuseUsedPercentage; scalar_t__ BTEfuseUsedBytes; int /*<<< orphan*/  fakeEfuseModifiedMap; int /*<<< orphan*/  fakeEfuseInitMap; int /*<<< orphan*/  fakeEfuseContent; scalar_t__ fakeEfuseUsedBytes; scalar_t__ fakeEfuseBank; } ;
struct dm_priv {scalar_t__* ThermalValue_HP; scalar_t__ ThermalValue_HP_index; scalar_t__ TM_Trigger; } ;
struct hal_com_data {int fw_ractrl; int bIQKInitialized; TYPE_2__ EfuseHal; scalar_t__ EfuseUsedPercentage; scalar_t__ EfuseUsedBytes; scalar_t__ LastHMEBoxNum; struct dm_priv dmpriv; } ;
struct TYPE_4__ {int /*<<< orphan*/  wireless_mode; } ;
struct adapter {TYPE_1__ registrypriv; } ;
struct TYPE_6__ {int /*<<< orphan*/  bkeepfwalive; } ;

/* Variables and functions */
 int EFUSE_BT_MAX_MAP_LEN ; 
 int EFUSE_MAX_BT_BANK ; 
 int EFUSE_MAX_HW_SIZE ; 
 int EFUSE_MAX_MAP_LEN ; 
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 size_t HP_THERMAL_NUM ; 
 int /*<<< orphan*/  WIRELESS_11BG_24N ; 
 TYPE_3__* adapter_to_pwrctl (struct adapter*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 

void rtl8723b_init_default_value(struct adapter *padapter)
{
	struct hal_com_data *pHalData;
	struct dm_priv *pdmpriv;
	u8 i;


	pHalData = GET_HAL_DATA(padapter);
	pdmpriv = &pHalData->dmpriv;

	padapter->registrypriv.wireless_mode = WIRELESS_11BG_24N;

	/*  init default value */
	pHalData->fw_ractrl = false;
	pHalData->bIQKInitialized = false;
	if (!adapter_to_pwrctl(padapter)->bkeepfwalive)
		pHalData->LastHMEBoxNum = 0;

	pHalData->bIQKInitialized = false;

	/*  init dm default value */
	pdmpriv->TM_Trigger = 0;/* for IQK */
/* 	pdmpriv->binitialized = false; */
/* 	pdmpriv->prv_traffic_idx = 3; */
/* 	pdmpriv->initialize = 0; */

	pdmpriv->ThermalValue_HP_index = 0;
	for (i = 0; i < HP_THERMAL_NUM; i++)
		pdmpriv->ThermalValue_HP[i] = 0;

	/*  init Efuse variables */
	pHalData->EfuseUsedBytes = 0;
	pHalData->EfuseUsedPercentage = 0;
#ifdef HAL_EFUSE_MEMORY
	pHalData->EfuseHal.fakeEfuseBank = 0;
	pHalData->EfuseHal.fakeEfuseUsedBytes = 0;
	memset(pHalData->EfuseHal.fakeEfuseContent, 0xFF, EFUSE_MAX_HW_SIZE);
	memset(pHalData->EfuseHal.fakeEfuseInitMap, 0xFF, EFUSE_MAX_MAP_LEN);
	memset(pHalData->EfuseHal.fakeEfuseModifiedMap, 0xFF, EFUSE_MAX_MAP_LEN);
	pHalData->EfuseHal.BTEfuseUsedBytes = 0;
	pHalData->EfuseHal.BTEfuseUsedPercentage = 0;
	memset(pHalData->EfuseHal.BTEfuseContent, 0xFF, EFUSE_MAX_BT_BANK*EFUSE_MAX_HW_SIZE);
	memset(pHalData->EfuseHal.BTEfuseInitMap, 0xFF, EFUSE_BT_MAX_MAP_LEN);
	memset(pHalData->EfuseHal.BTEfuseModifiedMap, 0xFF, EFUSE_BT_MAX_MAP_LEN);
	pHalData->EfuseHal.fakeBTEfuseUsedBytes = 0;
	memset(pHalData->EfuseHal.fakeBTEfuseContent, 0xFF, EFUSE_MAX_BT_BANK*EFUSE_MAX_HW_SIZE);
	memset(pHalData->EfuseHal.fakeBTEfuseInitMap, 0xFF, EFUSE_BT_MAX_MAP_LEN);
	memset(pHalData->EfuseHal.fakeBTEfuseModifiedMap, 0xFF, EFUSE_BT_MAX_MAP_LEN);
#endif
}