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
struct sta_info {int /*<<< orphan*/  mac_id; } ;
struct odm_dm_struct {int bWIFI_Direct; int bWIFI_Display; } ;
struct adapter {TYPE_1__* HalData; } ;
typedef  enum hal_odm_variable { ____Placeholder_hal_odm_variable } hal_odm_variable ;
struct TYPE_2__ {struct odm_dm_struct odmpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_88E (char*,int /*<<< orphan*/ ) ; 
#define  HAL_ODM_P2P_STATE 130 
#define  HAL_ODM_STA_INFO 129 
#define  HAL_ODM_WIFI_DISPLAY_STATE 128 
 int /*<<< orphan*/  ODM_CMNINFO_STA_STATUS ; 
 int /*<<< orphan*/  ODM_CmnInfoPtrArrayHook (struct odm_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sta_info*) ; 
 int /*<<< orphan*/  ODM_RAInfo_Init (struct odm_dm_struct*,int /*<<< orphan*/ ) ; 

void rtw_hal_set_odm_var(struct adapter *Adapter, enum hal_odm_variable eVariable, void *pValue1, bool bSet)
{
	struct odm_dm_struct *podmpriv = &Adapter->HalData->odmpriv;

	switch (eVariable) {
	case HAL_ODM_STA_INFO:
		{
			struct sta_info *psta = pValue1;

			if (bSet) {
				DBG_88E("### Set STA_(%d) info\n", psta->mac_id);
				ODM_CmnInfoPtrArrayHook(podmpriv, ODM_CMNINFO_STA_STATUS, psta->mac_id, psta);
				ODM_RAInfo_Init(podmpriv, psta->mac_id);
			} else {
				DBG_88E("### Clean STA_(%d) info\n", psta->mac_id);
				ODM_CmnInfoPtrArrayHook(podmpriv, ODM_CMNINFO_STA_STATUS, psta->mac_id, NULL);
		       }
		}
		break;
	case HAL_ODM_P2P_STATE:
		podmpriv->bWIFI_Direct = bSet;
		break;
	case HAL_ODM_WIFI_DISPLAY_STATE:
		podmpriv->bWIFI_Display = bSet;
		break;
	default:
		break;
	}
}