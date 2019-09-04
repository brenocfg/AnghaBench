#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ims_pcu {int update_firmware_status; TYPE_1__* dev; } ;
struct firmware {int /*<<< orphan*/  size; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMS_PCU_FIRMWARE_NAME ; 
 int /*<<< orphan*/  LAUNCH_APP ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int ims_pcu_count_fw_records (struct firmware const*) ; 
 int ims_pcu_execute_bl_command (struct ims_pcu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ims_pcu_flash_firmware (struct ims_pcu*,struct firmware const*,unsigned int) ; 
 int /*<<< orphan*/  sysfs_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int ims_pcu_handle_firmware_update(struct ims_pcu *pcu,
					  const struct firmware *fw)
{
	unsigned int n_fw_records;
	int retval;

	dev_info(pcu->dev, "Updating firmware %s, size: %zu\n",
		 IMS_PCU_FIRMWARE_NAME, fw->size);

	n_fw_records = ims_pcu_count_fw_records(fw);

	retval = ims_pcu_flash_firmware(pcu, fw, n_fw_records);
	if (retval)
		goto out;

	retval = ims_pcu_execute_bl_command(pcu, LAUNCH_APP, NULL, 0, 0);
	if (retval)
		dev_err(pcu->dev,
			"Failed to start application image, error: %d\n",
			retval);

out:
	pcu->update_firmware_status = retval;
	sysfs_notify(&pcu->dev->kobj, NULL, "update_firmware_status");
	return retval;
}