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
struct rtw_efuse {int crystal_cap; int pa_type_2g; int pa_type_5g; int lna_type_2g; int lna_type_5g; int channel_plan; int rf_board_option; int bt_setting; int share_ant; int regd; int btcoex; int ext_pa_2g; int ext_lna_2g; int ext_pa_5g; } ;
struct rtw_dev {int /*<<< orphan*/  mutex; struct rtw_efuse efuse; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rtw_check_supported_rfe (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_chip_efuse_disable (struct rtw_dev*) ; 
 int rtw_chip_efuse_enable (struct rtw_dev*) ; 
 int rtw_dump_hw_feature (struct rtw_dev*) ; 
 int rtw_parse_efuse_map (struct rtw_dev*) ; 

__attribute__((used)) static int rtw_chip_efuse_info_setup(struct rtw_dev *rtwdev)
{
	struct rtw_efuse *efuse = &rtwdev->efuse;
	int ret;

	mutex_lock(&rtwdev->mutex);

	/* power on mac to read efuse */
	ret = rtw_chip_efuse_enable(rtwdev);
	if (ret)
		goto out;

	ret = rtw_parse_efuse_map(rtwdev);
	if (ret)
		goto out;

	ret = rtw_dump_hw_feature(rtwdev);
	if (ret)
		goto out;

	ret = rtw_check_supported_rfe(rtwdev);
	if (ret)
		goto out;

	if (efuse->crystal_cap == 0xff)
		efuse->crystal_cap = 0;
	if (efuse->pa_type_2g == 0xff)
		efuse->pa_type_2g = 0;
	if (efuse->pa_type_5g == 0xff)
		efuse->pa_type_5g = 0;
	if (efuse->lna_type_2g == 0xff)
		efuse->lna_type_2g = 0;
	if (efuse->lna_type_5g == 0xff)
		efuse->lna_type_5g = 0;
	if (efuse->channel_plan == 0xff)
		efuse->channel_plan = 0x7f;
	if (efuse->rf_board_option == 0xff)
		efuse->rf_board_option = 0;
	if (efuse->bt_setting & BIT(0))
		efuse->share_ant = true;
	if (efuse->regd == 0xff)
		efuse->regd = 0;

	efuse->btcoex = (efuse->rf_board_option & 0xe0) == 0x20;
	efuse->ext_pa_2g = efuse->pa_type_2g & BIT(4) ? 1 : 0;
	efuse->ext_lna_2g = efuse->lna_type_2g & BIT(3) ? 1 : 0;
	efuse->ext_pa_5g = efuse->pa_type_5g & BIT(0) ? 1 : 0;
	efuse->ext_lna_2g = efuse->lna_type_5g & BIT(3) ? 1 : 0;

	rtw_chip_efuse_disable(rtwdev);

out:
	mutex_unlock(&rtwdev->mutex);
	return ret;
}