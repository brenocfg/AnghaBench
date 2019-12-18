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
typedef  int /*<<< orphan*/  u8 ;
struct rtw_efuse {int rf_board_option; int regd; int /*<<< orphan*/ * txpwr_idx_table; int /*<<< orphan*/  bt_setting; int /*<<< orphan*/ * country_code; int /*<<< orphan*/  channel_plan; int /*<<< orphan*/  lna_type_5g; int /*<<< orphan*/  lna_type_2g; int /*<<< orphan*/  pa_type_5g; int /*<<< orphan*/  pa_type_2g; int /*<<< orphan*/  crystal_cap; int /*<<< orphan*/  rfe_option; } ;
struct rtw_dev {struct rtw_efuse efuse; } ;
struct rtw8822b_efuse {int rf_board_option; int /*<<< orphan*/ * txpwr_idx_table; int /*<<< orphan*/  rf_bt_setting; int /*<<< orphan*/ * country_code; int /*<<< orphan*/  channel_plan; int /*<<< orphan*/ * lna_type_5g; int /*<<< orphan*/ * lna_type_2g; int /*<<< orphan*/  pa_type; int /*<<< orphan*/  xtal_k; int /*<<< orphan*/  rfe_option; } ;

/* Variables and functions */
 int ENOTSUPP ; 
#define  RTW_HCI_TYPE_PCIE 128 
 int /*<<< orphan*/  rtw8822be_efuse_parsing (struct rtw_efuse*,struct rtw8822b_efuse*) ; 
 int rtw_hci_type (struct rtw_dev*) ; 

__attribute__((used)) static int rtw8822b_read_efuse(struct rtw_dev *rtwdev, u8 *log_map)
{
	struct rtw_efuse *efuse = &rtwdev->efuse;
	struct rtw8822b_efuse *map;
	int i;

	map = (struct rtw8822b_efuse *)log_map;

	efuse->rfe_option = map->rfe_option;
	efuse->rf_board_option = map->rf_board_option;
	efuse->crystal_cap = map->xtal_k;
	efuse->pa_type_2g = map->pa_type;
	efuse->pa_type_5g = map->pa_type;
	efuse->lna_type_2g = map->lna_type_2g[0];
	efuse->lna_type_5g = map->lna_type_5g[0];
	efuse->channel_plan = map->channel_plan;
	efuse->country_code[0] = map->country_code[0];
	efuse->country_code[1] = map->country_code[1];
	efuse->bt_setting = map->rf_bt_setting;
	efuse->regd = map->rf_board_option & 0x7;

	for (i = 0; i < 4; i++)
		efuse->txpwr_idx_table[i] = map->txpwr_idx_table[i];

	switch (rtw_hci_type(rtwdev)) {
	case RTW_HCI_TYPE_PCIE:
		rtw8822be_efuse_parsing(efuse, map);
		break;
	default:
		/* unsupported now */
		return -ENOTSUPP;
	}

	return 0;
}