#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
struct sta_priv {int dummy; } ;
struct TYPE_7__ {int UndecoratedSmoothedPWDB; } ;
struct sta_info {TYPE_3__ rssi_stat; } ;
struct odm_dm_struct {int /*<<< orphan*/  DebugComponents; TYPE_4__* RAInfo; scalar_t__ SupportAbility; } ;
struct TYPE_5__ {int /*<<< orphan*/  MacAddress; } ;
struct TYPE_6__ {TYPE_1__ network; } ;
struct mlme_priv {TYPE_2__ cur_network; } ;
struct hal_data_8188e {size_t CurAntenna; size_t bDumpRxPkt; size_t bDumpTxPkt; struct odm_dm_struct odmpriv; int /*<<< orphan*/  AntDivCfg; } ;
struct adapter {struct mlme_priv mlmepriv; struct sta_priv stapriv; struct hal_data_8188e* HalData; } ;
typedef  enum hal_def_variable { ____Placeholder_hal_def_variable } hal_def_variable ;
struct TYPE_8__ {int /*<<< orphan*/  PTStage; int /*<<< orphan*/  DecisionRate; int /*<<< orphan*/  RateSGI; int /*<<< orphan*/  RAUseRate; int /*<<< orphan*/  RateID; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_88E (char*,...) ; 
 scalar_t__ DRVINFO_SZ ; 
#define  HAL_DEF_CURRENT_ANTENNA 142 
#define  HAL_DEF_DBG_DM_FUNC 141 
#define  HAL_DEF_DBG_DUMP_RXPKT 140 
#define  HAL_DEF_DBG_DUMP_TXPKT 139 
#define  HAL_DEF_DRVINFO_SZ 138 
#define  HAL_DEF_IS_SUPPORT_ANT_DIV 137 
#define  HAL_DEF_MAX_RECVBUF_SZ 136 
#define  HAL_DEF_PT_PWR_STATUS 135 
#define  HAL_DEF_RA_DECISION_RATE 134 
#define  HAL_DEF_RA_SGI 133 
#define  HAL_DEF_RX_PACKET_OFFSET 132 
#define  HAL_DEF_UNDERCORATEDSMOOTHEDPWDB 131 
#define  HW_DEF_ODM_DBG_FLAG 130 
#define  HW_DEF_RA_INFO_DUMP 129 
#define  HW_VAR_MAX_RX_AMPDU_FACTOR 128 
 scalar_t__ MAX_AMPDU_FACTOR_64K ; 
 scalar_t__ MAX_RECVBUF_SZ ; 
 size_t ODM_RA_GetDecisionRate_8188E (struct odm_dm_struct*,size_t) ; 
 size_t ODM_RA_GetHwPwrStatus_8188E (struct odm_dm_struct*,size_t) ; 
 size_t ODM_RA_GetShortGI_8188E (struct odm_dm_struct*,size_t) ; 
 scalar_t__ RXDESC_SIZE ; 
 size_t _FAIL ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 size_t _SUCCESS ; 
 int /*<<< orphan*/  check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 struct sta_info* rtw_get_stainfo (struct sta_priv*,int /*<<< orphan*/ ) ; 

u8 rtw_hal_get_def_var(struct adapter *Adapter, enum hal_def_variable eVariable,
		       void *pValue)
{
	struct hal_data_8188e *haldata = Adapter->HalData;
	u8 bResult = _SUCCESS;

	switch (eVariable) {
	case HAL_DEF_UNDERCORATEDSMOOTHEDPWDB:
		{
			struct mlme_priv *pmlmepriv = &Adapter->mlmepriv;
			struct sta_priv *pstapriv = &Adapter->stapriv;
			struct sta_info *psta;

			psta = rtw_get_stainfo(pstapriv, pmlmepriv->cur_network.network.MacAddress);
			if (psta)
				*((int *)pValue) = psta->rssi_stat.UndecoratedSmoothedPWDB;
		}
		break;
	case HAL_DEF_IS_SUPPORT_ANT_DIV:
		*((u8 *)pValue) = (haldata->AntDivCfg == 0) ? false : true;
		break;
	case HAL_DEF_CURRENT_ANTENNA:
		*((u8 *)pValue) = haldata->CurAntenna;
		break;
	case HAL_DEF_DRVINFO_SZ:
		*((u32 *)pValue) = DRVINFO_SZ;
		break;
	case HAL_DEF_MAX_RECVBUF_SZ:
		*((u32 *)pValue) = MAX_RECVBUF_SZ;
		break;
	case HAL_DEF_RX_PACKET_OFFSET:
		*((u32 *)pValue) = RXDESC_SIZE + DRVINFO_SZ;
		break;
	case HAL_DEF_DBG_DM_FUNC:
		*((u32 *)pValue) = haldata->odmpriv.SupportAbility;
		break;
	case HAL_DEF_RA_DECISION_RATE:
		{
			u8 MacID = *((u8 *)pValue);

			*((u8 *)pValue) = ODM_RA_GetDecisionRate_8188E(&haldata->odmpriv, MacID);
		}
		break;
	case HAL_DEF_RA_SGI:
		{
			u8 MacID = *((u8 *)pValue);

			*((u8 *)pValue) = ODM_RA_GetShortGI_8188E(&haldata->odmpriv, MacID);
		}
		break;
	case HAL_DEF_PT_PWR_STATUS:
		{
			u8 MacID = *((u8 *)pValue);

			*((u8 *)pValue) = ODM_RA_GetHwPwrStatus_8188E(&haldata->odmpriv, MacID);
		}
		break;
	case HW_VAR_MAX_RX_AMPDU_FACTOR:
		*((u32 *)pValue) = MAX_AMPDU_FACTOR_64K;
		break;
	case HW_DEF_RA_INFO_DUMP:
		{
			u8 entry_id = *((u8 *)pValue);

			if (check_fwstate(&Adapter->mlmepriv, _FW_LINKED)) {
				DBG_88E("============ RA status check ===================\n");
				DBG_88E("Mac_id:%d , RateID = %d, RAUseRate = 0x%08x, RateSGI = %d, DecisionRate = 0x%02x ,PTStage = %d\n",
					entry_id,
					haldata->odmpriv.RAInfo[entry_id].RateID,
					haldata->odmpriv.RAInfo[entry_id].RAUseRate,
					haldata->odmpriv.RAInfo[entry_id].RateSGI,
					haldata->odmpriv.RAInfo[entry_id].DecisionRate,
					haldata->odmpriv.RAInfo[entry_id].PTStage);
			}
		}
		break;
	case HW_DEF_ODM_DBG_FLAG:
		{
			struct odm_dm_struct *dm_ocm = &haldata->odmpriv;

			pr_info("dm_ocm->DebugComponents = 0x%llx\n", dm_ocm->DebugComponents);
		}
		break;
	case HAL_DEF_DBG_DUMP_RXPKT:
		*((u8 *)pValue) = haldata->bDumpRxPkt;
		break;
	case HAL_DEF_DBG_DUMP_TXPKT:
		*((u8 *)pValue) = haldata->bDumpTxPkt;
		break;
	default:
		bResult = _FAIL;
		break;
	}

	return bResult;
}