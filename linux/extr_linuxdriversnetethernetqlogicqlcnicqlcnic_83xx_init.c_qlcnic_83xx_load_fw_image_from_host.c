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
struct qlcnic_adapter {TYPE_2__* pdev; TYPE_1__* ahw; } ;
struct qlc_83xx_fw_info {int /*<<< orphan*/  fw_file_name; int /*<<< orphan*/  fw; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct qlc_83xx_fw_info* fw_info; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  QLCNIC_FW_IMG_VALID ; 
 int /*<<< orphan*/  QLC_83XX_BOOT_FROM_FILE ; 
 int /*<<< orphan*/  QLC_83XX_BOOT_FROM_FLASH ; 
 int /*<<< orphan*/  QLC_SHARED_REG_WR32 (struct qlcnic_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ qlcnic_83xx_copy_fw_file (struct qlcnic_adapter*) ; 
 scalar_t__ request_firmware (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qlcnic_83xx_load_fw_image_from_host(struct qlcnic_adapter *adapter)
{
	struct qlc_83xx_fw_info *fw_info = adapter->ahw->fw_info;
	int err = -EIO;

	if (request_firmware(&fw_info->fw, fw_info->fw_file_name,
			     &(adapter->pdev->dev))) {
		dev_err(&adapter->pdev->dev,
			"No file FW image, loading flash FW image.\n");
		QLC_SHARED_REG_WR32(adapter, QLCNIC_FW_IMG_VALID,
				    QLC_83XX_BOOT_FROM_FLASH);
	} else {
		if (qlcnic_83xx_copy_fw_file(adapter))
			return err;
		QLC_SHARED_REG_WR32(adapter, QLCNIC_FW_IMG_VALID,
				    QLC_83XX_BOOT_FROM_FILE);
	}

	return 0;
}