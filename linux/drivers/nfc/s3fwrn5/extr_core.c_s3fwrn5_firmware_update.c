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
struct s3fwrn5_info {int /*<<< orphan*/  fw_info; TYPE_2__* ndev; } ;
struct TYPE_4__ {TYPE_1__* nfc_dev; int /*<<< orphan*/  manufact_specific_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  S3FWRN5_MODE_COLD ; 
 int /*<<< orphan*/  S3FWRN5_MODE_FW ; 
 int /*<<< orphan*/  S3FWRN5_MODE_NCI ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int s3fwrn5_fw_check_version (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3fwrn5_fw_cleanup (int /*<<< orphan*/ *) ; 
 int s3fwrn5_fw_download (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s3fwrn5_fw_init (int /*<<< orphan*/ *,char*) ; 
 int s3fwrn5_fw_setup (int /*<<< orphan*/ *) ; 
 int s3fwrn5_nci_rf_configure (struct s3fwrn5_info*,char*) ; 
 int /*<<< orphan*/  s3fwrn5_set_mode (struct s3fwrn5_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3fwrn5_set_wake (struct s3fwrn5_info*,int) ; 

__attribute__((used)) static int s3fwrn5_firmware_update(struct s3fwrn5_info *info)
{
	bool need_update;
	int ret;

	s3fwrn5_fw_init(&info->fw_info, "sec_s3fwrn5_firmware.bin");

	/* Update firmware */

	s3fwrn5_set_wake(info, false);
	s3fwrn5_set_mode(info, S3FWRN5_MODE_FW);

	ret = s3fwrn5_fw_setup(&info->fw_info);
	if (ret < 0)
		return ret;

	need_update = s3fwrn5_fw_check_version(&info->fw_info,
		info->ndev->manufact_specific_info);
	if (!need_update)
		goto out;

	dev_info(&info->ndev->nfc_dev->dev, "Detected new firmware version\n");

	ret = s3fwrn5_fw_download(&info->fw_info);
	if (ret < 0)
		goto out;

	/* Update RF configuration */

	s3fwrn5_set_mode(info, S3FWRN5_MODE_NCI);

	s3fwrn5_set_wake(info, true);
	ret = s3fwrn5_nci_rf_configure(info, "sec_s3fwrn5_rfreg.bin");
	s3fwrn5_set_wake(info, false);

out:
	s3fwrn5_set_mode(info, S3FWRN5_MODE_COLD);
	s3fwrn5_fw_cleanup(&info->fw_info);
	return ret;
}