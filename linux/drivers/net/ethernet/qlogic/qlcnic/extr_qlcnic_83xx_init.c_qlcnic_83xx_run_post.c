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
typedef  int u32 ;
struct qlcnic_adapter {TYPE_2__* ahw; TYPE_1__* pdev; } ;
struct qlc_83xx_fw_info {int /*<<< orphan*/  fw_file_name; int /*<<< orphan*/  fw; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int post_mode; struct qlc_83xx_fw_info* fw_info; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  QLCNIC_FW_IMG_VALID ; 
 int /*<<< orphan*/  QLC_83XX_BOOT_FROM_FILE ; 
#define  QLC_83XX_POST_ASIC_MEMORY_TEST_FAIL 135 
#define  QLC_83XX_POST_ASIC_STRESS_TEST_FAIL 134 
#define  QLC_83XX_POST_DDR_TEST_FAIL 133 
#define  QLC_83XX_POST_FAST_MODE 132 
 int /*<<< orphan*/  QLC_83XX_POST_FAST_MODE_TIMEOUT ; 
#define  QLC_83XX_POST_FLASH_TEST_FAIL 131 
 int /*<<< orphan*/  QLC_83XX_POST_FW_FILE_NAME ; 
#define  QLC_83XX_POST_MEDIUM_MODE 130 
 int /*<<< orphan*/  QLC_83XX_POST_MED_MODE_TIMEOUT ; 
 int /*<<< orphan*/  QLC_83XX_POST_MODE_REG ; 
#define  QLC_83XX_POST_PASS 129 
 int /*<<< orphan*/  QLC_83XX_POST_SIGNATURE_REG ; 
#define  QLC_83XX_POST_SLOW_MODE 128 
 int /*<<< orphan*/  QLC_83XX_POST_SLOW_MODE_TIMEOUT ; 
 int /*<<< orphan*/  QLC_FW_FILE_NAME_LEN ; 
 int /*<<< orphan*/  QLC_SHARED_REG_WR32 (struct qlcnic_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int qlcnic_83xx_copy_fw_file (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_start_hw (struct qlcnic_adapter*) ; 
 int qlcnic_ind_rd (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_ind_wr (struct qlcnic_adapter*,int /*<<< orphan*/ ,int) ; 
 int request_firmware (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qlcnic_83xx_run_post(struct qlcnic_adapter *adapter)
{
	struct qlc_83xx_fw_info *fw_info = adapter->ahw->fw_info;
	struct device *dev = &adapter->pdev->dev;
	int timeout, count, ret = 0;
	u32 signature;

	/* Set timeout values with extra 2 seconds of buffer */
	switch (adapter->ahw->post_mode) {
	case QLC_83XX_POST_FAST_MODE:
		timeout = QLC_83XX_POST_FAST_MODE_TIMEOUT + 2000;
		break;
	case QLC_83XX_POST_MEDIUM_MODE:
		timeout = QLC_83XX_POST_MED_MODE_TIMEOUT + 2000;
		break;
	case QLC_83XX_POST_SLOW_MODE:
		timeout = QLC_83XX_POST_SLOW_MODE_TIMEOUT + 2000;
		break;
	default:
		return -EINVAL;
	}

	strncpy(fw_info->fw_file_name, QLC_83XX_POST_FW_FILE_NAME,
		QLC_FW_FILE_NAME_LEN);

	ret = request_firmware(&fw_info->fw, fw_info->fw_file_name, dev);
	if (ret) {
		dev_err(dev, "POST firmware can not be loaded, skipping POST\n");
		return 0;
	}

	ret = qlcnic_83xx_copy_fw_file(adapter);
	if (ret)
		return ret;

	/* clear QLC_83XX_POST_SIGNATURE_REG register */
	qlcnic_ind_wr(adapter, QLC_83XX_POST_SIGNATURE_REG, 0);

	/* Set POST mode */
	qlcnic_ind_wr(adapter, QLC_83XX_POST_MODE_REG,
		      adapter->ahw->post_mode);

	QLC_SHARED_REG_WR32(adapter, QLCNIC_FW_IMG_VALID,
			    QLC_83XX_BOOT_FROM_FILE);

	qlcnic_83xx_start_hw(adapter);

	count = 0;
	do {
		msleep(100);
		count += 100;

		signature = qlcnic_ind_rd(adapter, QLC_83XX_POST_SIGNATURE_REG);
		if (signature == QLC_83XX_POST_PASS)
			break;
	} while (timeout > count);

	if (timeout <= count) {
		dev_err(dev, "POST timed out, signature = 0x%08x\n", signature);
		return -EIO;
	}

	switch (signature) {
	case QLC_83XX_POST_PASS:
		dev_info(dev, "POST passed, Signature = 0x%08x\n", signature);
		break;
	case QLC_83XX_POST_ASIC_STRESS_TEST_FAIL:
		dev_err(dev, "POST failed, Test case : ASIC STRESS TEST, Signature = 0x%08x\n",
			signature);
		ret = -EIO;
		break;
	case QLC_83XX_POST_DDR_TEST_FAIL:
		dev_err(dev, "POST failed, Test case : DDT TEST, Signature = 0x%08x\n",
			signature);
		ret = -EIO;
		break;
	case QLC_83XX_POST_ASIC_MEMORY_TEST_FAIL:
		dev_err(dev, "POST failed, Test case : ASIC MEMORY TEST, Signature = 0x%08x\n",
			signature);
		ret = -EIO;
		break;
	case QLC_83XX_POST_FLASH_TEST_FAIL:
		dev_err(dev, "POST failed, Test case : FLASH TEST, Signature = 0x%08x\n",
			signature);
		ret = -EIO;
		break;
	default:
		dev_err(dev, "POST failed, Test case : INVALID, Signature = 0x%08x\n",
			signature);
		ret = -EIO;
		break;
	}

	return ret;
}