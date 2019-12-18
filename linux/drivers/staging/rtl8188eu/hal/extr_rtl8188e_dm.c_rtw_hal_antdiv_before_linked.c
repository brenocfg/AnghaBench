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
typedef  int u8 ;
struct sw_ant_switch {int SWAS_NoLink_State; scalar_t__ CurAntenna; } ;
struct odm_dm_struct {struct sw_ant_switch DM_SWAT_Table; } ;
struct mlme_priv {int dummy; } ;
struct adapter {TYPE_1__* HalData; struct mlme_priv mlmepriv; } ;
struct TYPE_2__ {scalar_t__ AntDivCfg; struct odm_dm_struct odmpriv; } ;

/* Variables and functions */
 scalar_t__ Antenna_A ; 
 scalar_t__ Antenna_B ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_antenna_select_cmd (struct adapter*,scalar_t__,int) ; 

u8 rtw_hal_antdiv_before_linked(struct adapter *Adapter)
{
	struct odm_dm_struct *dm_odm = &Adapter->HalData->odmpriv;
	struct sw_ant_switch *dm_swat_tbl = &dm_odm->DM_SWAT_Table;
	struct mlme_priv *pmlmepriv = &(Adapter->mlmepriv);

	/*  Condition that does not need to use antenna diversity. */
	if (Adapter->HalData->AntDivCfg == 0)
		return false;

	if (check_fwstate(pmlmepriv, _FW_LINKED))
		return false;

	if (dm_swat_tbl->SWAS_NoLink_State == 0) {
		/* switch channel */
		dm_swat_tbl->SWAS_NoLink_State = 1;
		dm_swat_tbl->CurAntenna = (dm_swat_tbl->CurAntenna == Antenna_A) ? Antenna_B : Antenna_A;

		rtw_antenna_select_cmd(Adapter, dm_swat_tbl->CurAntenna, false);
		return true;
	} else {
		dm_swat_tbl->SWAS_NoLink_State = 0;
		return false;
	}
}