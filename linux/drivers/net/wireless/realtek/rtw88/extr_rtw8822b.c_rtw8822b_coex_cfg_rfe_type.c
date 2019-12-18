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
struct rtw_efuse {int rfe_option; scalar_t__ share_ant; } ;
struct rtw_coex_rfe {int rfe_module_type; int ant_switch_diversity; int ant_switch_exist; int wlg_at_btg; int ant_switch_with_bt; scalar_t__ ant_switch_polarity; } ;
struct rtw_coex {struct rtw_coex_rfe rfe; } ;
struct rtw_dev {struct rtw_efuse efuse; struct rtw_coex coex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_LTE_COEX_EN ; 
 int BIT_RFE_BUF_EN ; 
 int /*<<< orphan*/  COEX_SCBD_EXTFEM ; 
 int /*<<< orphan*/  LTE_BT_TRX_CTRL ; 
 int /*<<< orphan*/  LTE_COEX_CTRL ; 
 int /*<<< orphan*/  LTE_WL_TRX_CTRL ; 
 int /*<<< orphan*/  MASKLWORD ; 
 scalar_t__ REG_RFESEL_CTRL ; 
 int /*<<< orphan*/  REG_RFE_CTRL_E ; 
 scalar_t__ REG_RFE_INV16 ; 
 int /*<<< orphan*/  rtw_coex_write_indirect_reg (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_coex_write_scbd (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_write8 (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_write8_mask (struct rtw_dev*,scalar_t__,int,int) ; 

__attribute__((used)) static void rtw8822b_coex_cfg_rfe_type(struct rtw_dev *rtwdev)
{
	struct rtw_coex *coex = &rtwdev->coex;
	struct rtw_coex_rfe *coex_rfe = &coex->rfe;
	struct rtw_efuse *efuse = &rtwdev->efuse;
	bool is_ext_fem = false;

	coex_rfe->rfe_module_type = rtwdev->efuse.rfe_option;
	coex_rfe->ant_switch_polarity = 0;
	coex_rfe->ant_switch_diversity = false;
	if (coex_rfe->rfe_module_type == 0x12 ||
	    coex_rfe->rfe_module_type == 0x15 ||
	    coex_rfe->rfe_module_type == 0x16)
		coex_rfe->ant_switch_exist = false;
	else
		coex_rfe->ant_switch_exist = true;

	if (coex_rfe->rfe_module_type == 2 ||
	    coex_rfe->rfe_module_type == 4) {
		rtw_coex_write_scbd(rtwdev, COEX_SCBD_EXTFEM, true);
		is_ext_fem = true;
	} else {
		rtw_coex_write_scbd(rtwdev, COEX_SCBD_EXTFEM, false);
	}

	coex_rfe->wlg_at_btg = false;

	if (efuse->share_ant &&
	    coex_rfe->ant_switch_exist && !is_ext_fem)
		coex_rfe->ant_switch_with_bt = true;
	else
		coex_rfe->ant_switch_with_bt = false;

	/* Ext switch buffer mux */
	rtw_write8(rtwdev, REG_RFE_CTRL_E, 0xff);
	rtw_write8_mask(rtwdev, REG_RFESEL_CTRL + 1, 0x3, 0x0);
	rtw_write8_mask(rtwdev, REG_RFE_INV16, BIT_RFE_BUF_EN, 0x0);

	/* Disable LTE Coex Function in WiFi side */
	rtw_coex_write_indirect_reg(rtwdev, LTE_COEX_CTRL, BIT_LTE_COEX_EN, 0);

	/* BTC_CTT_WL_VS_LTE */
	rtw_coex_write_indirect_reg(rtwdev, LTE_WL_TRX_CTRL, MASKLWORD, 0xffff);

	/* BTC_CTT_BT_VS_LTE */
	rtw_coex_write_indirect_reg(rtwdev, LTE_BT_TRX_CTRL, MASKLWORD, 0xffff);
}