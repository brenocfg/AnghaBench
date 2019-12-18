#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct rtw_phy_cond {int cut; int pkg; int plat; int /*<<< orphan*/  intf; int /*<<< orphan*/  rfe; int /*<<< orphan*/  member_0; } ;
struct rtw_hal {int cut_version; struct rtw_phy_cond phy_cond; } ;
struct rtw_efuse {int /*<<< orphan*/  rfe_option; } ;
struct rtw_dev {struct rtw_efuse efuse; struct rtw_hal hal; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTF_PCIE ; 
 int /*<<< orphan*/  INTF_SDIO ; 
 int /*<<< orphan*/  INTF_USB ; 
 int /*<<< orphan*/  RTW_DBG_PHY ; 
#define  RTW_HCI_TYPE_PCIE 130 
#define  RTW_HCI_TYPE_SDIO 129 
#define  RTW_HCI_TYPE_USB 128 
 int /*<<< orphan*/  rtw_dbg (struct rtw_dev*,int /*<<< orphan*/ ,char*,int) ; 
 int rtw_hci_type (struct rtw_dev*) ; 

void rtw_phy_setup_phy_cond(struct rtw_dev *rtwdev, u32 pkg)
{
	struct rtw_hal *hal = &rtwdev->hal;
	struct rtw_efuse *efuse = &rtwdev->efuse;
	struct rtw_phy_cond cond = {0};

	cond.cut = hal->cut_version ? hal->cut_version : 15;
	cond.pkg = pkg ? pkg : 15;
	cond.plat = 0x04;
	cond.rfe = efuse->rfe_option;

	switch (rtw_hci_type(rtwdev)) {
	case RTW_HCI_TYPE_USB:
		cond.intf = INTF_USB;
		break;
	case RTW_HCI_TYPE_SDIO:
		cond.intf = INTF_SDIO;
		break;
	case RTW_HCI_TYPE_PCIE:
	default:
		cond.intf = INTF_PCIE;
		break;
	}

	hal->phy_cond = cond;

	rtw_dbg(rtwdev, RTW_DBG_PHY, "phy cond=0x%08x\n", *((u32 *)&hal->phy_cond));
}