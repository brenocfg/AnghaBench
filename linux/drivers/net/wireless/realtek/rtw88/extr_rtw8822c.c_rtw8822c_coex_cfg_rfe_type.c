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
struct rtw_efuse {scalar_t__ share_ant; int /*<<< orphan*/  rfe_option; } ;
struct rtw_coex_rfe {int ant_switch_exist; int ant_switch_with_bt; int ant_switch_diversity; int wlg_at_btg; scalar_t__ ant_switch_polarity; int /*<<< orphan*/  rfe_module_type; } ;
struct rtw_coex {struct rtw_coex_rfe rfe; } ;
struct rtw_dev {struct rtw_efuse efuse; struct rtw_coex coex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_LTE_COEX_EN ; 
 int /*<<< orphan*/  MASKLWORD ; 
 int /*<<< orphan*/  rtw_coex_write_indirect_reg (struct rtw_dev*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtw8822c_coex_cfg_rfe_type(struct rtw_dev *rtwdev)
{
	struct rtw_coex *coex = &rtwdev->coex;
	struct rtw_coex_rfe *coex_rfe = &coex->rfe;
	struct rtw_efuse *efuse = &rtwdev->efuse;

	coex_rfe->rfe_module_type = rtwdev->efuse.rfe_option;
	coex_rfe->ant_switch_polarity = 0;
	coex_rfe->ant_switch_exist = false;
	coex_rfe->ant_switch_with_bt = false;
	coex_rfe->ant_switch_diversity = false;

	if (efuse->share_ant)
		coex_rfe->wlg_at_btg = true;
	else
		coex_rfe->wlg_at_btg = false;

	/* disable LTE coex in wifi side */
	rtw_coex_write_indirect_reg(rtwdev, 0x38, BIT_LTE_COEX_EN, 0x0);
	rtw_coex_write_indirect_reg(rtwdev, 0xa0, MASKLWORD, 0xffff);
	rtw_coex_write_indirect_reg(rtwdev, 0xa4, MASKLWORD, 0xffff);
}