#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u1H2CAoacRsvdPageParm ;
struct mlme_priv {int dummy; } ;
struct adapter {struct mlme_priv mlmepriv; } ;
struct TYPE_5__ {int /*<<< orphan*/  pno_in_resume; } ;
struct TYPE_4__ {int /*<<< orphan*/  LocPNOInfo; int /*<<< orphan*/  LocGTKEXTMEM; int /*<<< orphan*/  LocGTKInfo; int /*<<< orphan*/  LocGTKRsp; int /*<<< orphan*/  LocArpRsp; int /*<<< orphan*/  LocRemoteCtrlInfo; int /*<<< orphan*/  LocNetList; int /*<<< orphan*/  LocProbeReq; int /*<<< orphan*/  LocNbrAdv; } ;
typedef  TYPE_1__* PRSVDPAGE_LOC ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  FillH2CCmd8723B (struct adapter*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  H2C_8723B_AOAC_RSVD_PAGE ; 
 int /*<<< orphan*/  H2C_AOAC_RSVDPAGE3 ; 
 int H2C_AOAC_RSVDPAGE_LOC_LEN ; 
 int /*<<< orphan*/  RT_PRINT_DATA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_H2CCMD_AOAC_RSVDPAGE_LOC_ARP_RSP (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_H2CCMD_AOAC_RSVDPAGE_LOC_GTK_EXT_MEM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_H2CCMD_AOAC_RSVDPAGE_LOC_GTK_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_H2CCMD_AOAC_RSVDPAGE_LOC_GTK_RSP (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_H2CCMD_AOAC_RSVDPAGE_LOC_NLO_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_H2CCMD_AOAC_RSVDPAGE_LOC_REMOTE_WAKE_CTRL_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 int /*<<< orphan*/  _drv_always_ ; 
 int /*<<< orphan*/  _module_hal_init_c_ ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 TYPE_3__* pwrpriv ; 

__attribute__((used)) static void rtl8723b_set_FwAoacRsvdPage_cmd(struct adapter *padapter, PRSVDPAGE_LOC rsvdpageloc)
{
#ifdef CONFIG_WOWLAN
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	u8 u1H2CAoacRsvdPageParm[H2C_AOAC_RSVDPAGE_LOC_LEN] = {0};

	DBG_871X("8723BAOACRsvdPageLoc: RWC =%d ArpRsp =%d NbrAdv =%d GtkRsp =%d GtkInfo =%d ProbeReq =%d NetworkList =%d\n",
			rsvdpageloc->LocRemoteCtrlInfo, rsvdpageloc->LocArpRsp,
			rsvdpageloc->LocNbrAdv, rsvdpageloc->LocGTKRsp,
			rsvdpageloc->LocGTKInfo, rsvdpageloc->LocProbeReq,
			rsvdpageloc->LocNetList);

	if (check_fwstate(pmlmepriv, _FW_LINKED)) {
		SET_H2CCMD_AOAC_RSVDPAGE_LOC_REMOTE_WAKE_CTRL_INFO(u1H2CAoacRsvdPageParm, rsvdpageloc->LocRemoteCtrlInfo);
		SET_H2CCMD_AOAC_RSVDPAGE_LOC_ARP_RSP(u1H2CAoacRsvdPageParm, rsvdpageloc->LocArpRsp);
		/* SET_H2CCMD_AOAC_RSVDPAGE_LOC_NEIGHBOR_ADV(u1H2CAoacRsvdPageParm, rsvdpageloc->LocNbrAdv); */
		SET_H2CCMD_AOAC_RSVDPAGE_LOC_GTK_RSP(u1H2CAoacRsvdPageParm, rsvdpageloc->LocGTKRsp);
		SET_H2CCMD_AOAC_RSVDPAGE_LOC_GTK_INFO(u1H2CAoacRsvdPageParm, rsvdpageloc->LocGTKInfo);
#ifdef CONFIG_GTK_OL
		SET_H2CCMD_AOAC_RSVDPAGE_LOC_GTK_EXT_MEM(u1H2CAoacRsvdPageParm, rsvdpageloc->LocGTKEXTMEM);
#endif /*  CONFIG_GTK_OL */
		RT_PRINT_DATA(_module_hal_init_c_, _drv_always_, "u1H2CAoacRsvdPageParm:", u1H2CAoacRsvdPageParm, H2C_AOAC_RSVDPAGE_LOC_LEN);
		FillH2CCmd8723B(padapter, H2C_8723B_AOAC_RSVD_PAGE, H2C_AOAC_RSVDPAGE_LOC_LEN, u1H2CAoacRsvdPageParm);
	} else {
#ifdef CONFIG_PNO_SUPPORT
		if (!pwrpriv->pno_in_resume) {
			DBG_871X("NLO_INFO =%d\n", rsvdpageloc->LocPNOInfo);
			memset(&u1H2CAoacRsvdPageParm, 0, sizeof(u1H2CAoacRsvdPageParm));
			SET_H2CCMD_AOAC_RSVDPAGE_LOC_NLO_INFO(u1H2CAoacRsvdPageParm, rsvdpageloc->LocPNOInfo);
			FillH2CCmd8723B(padapter, H2C_AOAC_RSVDPAGE3, H2C_AOAC_RSVDPAGE_LOC_LEN, u1H2CAoacRsvdPageParm);
			msleep(10);
		}
#endif
	}

#endif /*  CONFIG_WOWLAN */
}