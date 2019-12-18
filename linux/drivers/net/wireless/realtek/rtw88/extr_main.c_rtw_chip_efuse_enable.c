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
struct rtw_fw_state {int /*<<< orphan*/  firmware; int /*<<< orphan*/  completion; } ;
struct rtw_dev {struct rtw_fw_state fw; } ;

/* Variables and functions */
 int /*<<< orphan*/  C2H_HW_FEATURE_DUMP ; 
 int EINVAL ; 
 int /*<<< orphan*/  REG_C2HEVT ; 
 int rtw_download_firmware (struct rtw_dev*,struct rtw_fw_state*) ; 
 int /*<<< orphan*/  rtw_err (struct rtw_dev*,char*) ; 
 int rtw_hci_setup (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_mac_power_off (struct rtw_dev*) ; 
 int rtw_mac_power_on (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_write8 (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rtw_chip_efuse_enable(struct rtw_dev *rtwdev)
{
	struct rtw_fw_state *fw = &rtwdev->fw;
	int ret;

	ret = rtw_hci_setup(rtwdev);
	if (ret) {
		rtw_err(rtwdev, "failed to setup hci\n");
		goto err;
	}

	ret = rtw_mac_power_on(rtwdev);
	if (ret) {
		rtw_err(rtwdev, "failed to power on mac\n");
		goto err;
	}

	rtw_write8(rtwdev, REG_C2HEVT, C2H_HW_FEATURE_DUMP);

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

	return 0;

err_off:
	rtw_mac_power_off(rtwdev);

err:
	return ret;
}