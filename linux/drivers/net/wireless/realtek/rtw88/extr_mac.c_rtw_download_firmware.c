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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct rtw_fw_state {TYPE_1__* firmware; } ;
struct TYPE_4__ {scalar_t__ seq; scalar_t__ last_box_num; } ;
struct rtw_dev {TYPE_2__ h2c; } ;
struct rtw_backup_info {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_FEN_CPUEN ; 
 int /*<<< orphan*/  BIT_MCUFWDL_EN ; 
 int DLFW_RESTORE_REG_NUM ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  REG_MCUFW_CTRL ; 
 scalar_t__ REG_SYS_FUNC_EN ; 
 int /*<<< orphan*/  RTW_FLAG_FW_RUNNING ; 
 int /*<<< orphan*/  check_firmware_size (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  download_firmware_end_flow (struct rtw_dev*) ; 
 int /*<<< orphan*/  download_firmware_reg_backup (struct rtw_dev*,struct rtw_backup_info*) ; 
 int /*<<< orphan*/  download_firmware_reg_restore (struct rtw_dev*,struct rtw_backup_info*,int) ; 
 int /*<<< orphan*/  download_firmware_reset_platform (struct rtw_dev*) ; 
 int download_firmware_validate (struct rtw_dev*) ; 
 int /*<<< orphan*/  ltecoex_read_reg (struct rtw_dev*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ltecoex_reg_write (struct rtw_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_flag_set (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_hci_setup (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_write8_clr (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write8_set (struct rtw_dev*,scalar_t__,int /*<<< orphan*/ ) ; 
 int start_download_firmware (struct rtw_dev*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_firmware_info (struct rtw_dev*,struct rtw_fw_state*) ; 
 int /*<<< orphan*/  wlan_cpu_enable (struct rtw_dev*,int) ; 

int rtw_download_firmware(struct rtw_dev *rtwdev, struct rtw_fw_state *fw)
{
	struct rtw_backup_info bckp[DLFW_RESTORE_REG_NUM];
	const u8 *data = fw->firmware->data;
	u32 size = fw->firmware->size;
	u32 ltecoex_bckp;
	int ret;

	if (!check_firmware_size(data, size))
		return -EINVAL;

	if (!ltecoex_read_reg(rtwdev, 0x38, &ltecoex_bckp))
		return -EBUSY;

	wlan_cpu_enable(rtwdev, false);

	download_firmware_reg_backup(rtwdev, bckp);
	download_firmware_reset_platform(rtwdev);

	ret = start_download_firmware(rtwdev, data, size);
	if (ret)
		goto dlfw_fail;

	download_firmware_reg_restore(rtwdev, bckp, DLFW_RESTORE_REG_NUM);

	download_firmware_end_flow(rtwdev);

	wlan_cpu_enable(rtwdev, true);

	if (!ltecoex_reg_write(rtwdev, 0x38, ltecoex_bckp))
		return -EBUSY;

	ret = download_firmware_validate(rtwdev);
	if (ret)
		goto dlfw_fail;

	update_firmware_info(rtwdev, fw);

	/* reset desc and index */
	rtw_hci_setup(rtwdev);

	rtwdev->h2c.last_box_num = 0;
	rtwdev->h2c.seq = 0;

	rtw_flag_set(rtwdev, RTW_FLAG_FW_RUNNING);

	return 0;

dlfw_fail:
	/* Disable FWDL_EN */
	rtw_write8_clr(rtwdev, REG_MCUFW_CTRL, BIT_MCUFWDL_EN);
	rtw_write8_set(rtwdev, REG_SYS_FUNC_EN + 1, BIT_FEN_CPUEN);

	return ret;
}