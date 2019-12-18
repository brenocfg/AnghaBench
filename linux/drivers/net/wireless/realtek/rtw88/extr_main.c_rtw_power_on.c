#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rtw_fw_state {int /*<<< orphan*/  firmware; int /*<<< orphan*/  completion; } ;
struct TYPE_4__ {int /*<<< orphan*/  btcoex; } ;
struct rtw_dev {TYPE_2__ efuse; struct rtw_fw_state fw; struct rtw_chip_info* chip; } ;
struct rtw_chip_info {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* phy_set_param ) (struct rtw_dev*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  rtw_coex_init_hw_config (struct rtw_dev*,int) ; 
 int /*<<< orphan*/  rtw_coex_power_on_setting (struct rtw_dev*) ; 
 int rtw_download_firmware (struct rtw_dev*,struct rtw_fw_state*) ; 
 int /*<<< orphan*/  rtw_err (struct rtw_dev*,char*) ; 
 int /*<<< orphan*/  rtw_fw_send_general_info (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_fw_send_phydm_info (struct rtw_dev*) ; 
 int rtw_hci_setup (struct rtw_dev*) ; 
 int rtw_hci_start (struct rtw_dev*) ; 
 int rtw_mac_init (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_mac_power_off (struct rtw_dev*) ; 
 int rtw_mac_power_on (struct rtw_dev*) ; 
 int /*<<< orphan*/  stub1 (struct rtw_dev*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rtw_power_on(struct rtw_dev *rtwdev)
{
	struct rtw_chip_info *chip = rtwdev->chip;
	struct rtw_fw_state *fw = &rtwdev->fw;
	bool wifi_only;
	int ret;

	ret = rtw_hci_setup(rtwdev);
	if (ret) {
		rtw_err(rtwdev, "failed to setup hci\n");
		goto err;
	}

	/* power on MAC before firmware downloaded */
	ret = rtw_mac_power_on(rtwdev);
	if (ret) {
		rtw_err(rtwdev, "failed to power on mac\n");
		goto err;
	}

	wait_for_completion(&fw->completion);
	if (!fw->firmware) {
		ret = -EINVAL;
		rtw_err(rtwdev, "failed to load firmware\n");
		goto err;
	}

	ret = rtw_download_firmware(rtwdev, fw);
	if (ret) {
		rtw_err(rtwdev, "failed to download firmware\n");
		goto err_off;
	}

	/* config mac after firmware downloaded */
	ret = rtw_mac_init(rtwdev);
	if (ret) {
		rtw_err(rtwdev, "failed to configure mac\n");
		goto err_off;
	}

	chip->ops->phy_set_param(rtwdev);

	ret = rtw_hci_start(rtwdev);
	if (ret) {
		rtw_err(rtwdev, "failed to start hci\n");
		goto err_off;
	}

	/* send H2C after HCI has started */
	rtw_fw_send_general_info(rtwdev);
	rtw_fw_send_phydm_info(rtwdev);

	wifi_only = !rtwdev->efuse.btcoex;
	rtw_coex_power_on_setting(rtwdev);
	rtw_coex_init_hw_config(rtwdev, wifi_only);

	return 0;

err_off:
	rtw_mac_power_off(rtwdev);

err:
	return ret;
}