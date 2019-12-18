#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sas_ha_struct {struct pm8001_hba_info* lldd_ha; } ;
struct pm8001_hba_info {scalar_t__ fw_status; int /*<<< orphan*/  fw_image; int /*<<< orphan*/  dev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int code; int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EACCES ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ FAIL_OPEN_BIOS_FILE ; 
 scalar_t__ FAIL_OUT_MEMORY ; 
 void* FAIL_PARAMETERS ; 
 int FLASH_CMD_NONE ; 
 int FLASH_CMD_UPDATE ; 
 scalar_t__ FLASH_IN_PROGRESS ; 
 scalar_t__ FLASH_OK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PM8001_FAIL_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 struct sas_ha_struct* SHOST_TO_SAS_HA (struct Scsi_Host*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 TYPE_1__* flash_command_table ; 
 char* kcalloc (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_printk (char*,char*,int) ; 
 int pm8001_set_nvmd (struct pm8001_hba_info*) ; 
 int pm8001_update_flash (struct pm8001_hba_info*) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ ) ; 
 int request_firmware (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int sscanf (char const*,char*,char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static ssize_t pm8001_store_update_fw(struct device *cdev,
				      struct device_attribute *attr,
				      const char *buf, size_t count)
{
	struct Scsi_Host *shost = class_to_shost(cdev);
	struct sas_ha_struct *sha = SHOST_TO_SAS_HA(shost);
	struct pm8001_hba_info *pm8001_ha = sha->lldd_ha;
	char *cmd_ptr, *filename_ptr;
	int res, i;
	int flash_command = FLASH_CMD_NONE;
	int ret;

	if (!capable(CAP_SYS_ADMIN))
		return -EACCES;

	/* this test protects us from running two flash processes at once,
	 * so we should start with this test */
	if (pm8001_ha->fw_status == FLASH_IN_PROGRESS)
		return -EINPROGRESS;
	pm8001_ha->fw_status = FLASH_IN_PROGRESS;

	cmd_ptr = kcalloc(count, 2, GFP_KERNEL);
	if (!cmd_ptr) {
		pm8001_ha->fw_status = FAIL_OUT_MEMORY;
		return -ENOMEM;
	}

	filename_ptr = cmd_ptr + count;
	res = sscanf(buf, "%s %s", cmd_ptr, filename_ptr);
	if (res != 2) {
		pm8001_ha->fw_status = FAIL_PARAMETERS;
		ret = -EINVAL;
		goto out;
	}

	for (i = 0; flash_command_table[i].code != FLASH_CMD_NONE; i++) {
		if (!memcmp(flash_command_table[i].command,
				 cmd_ptr, strlen(cmd_ptr))) {
			flash_command = flash_command_table[i].code;
			break;
		}
	}
	if (flash_command == FLASH_CMD_NONE) {
		pm8001_ha->fw_status = FAIL_PARAMETERS;
		ret = -EINVAL;
		goto out;
	}

	ret = request_firmware(&pm8001_ha->fw_image,
			       filename_ptr,
			       pm8001_ha->dev);

	if (ret) {
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk(
			"Failed to load firmware image file %s,	error %d\n",
			filename_ptr, ret));
		pm8001_ha->fw_status = FAIL_OPEN_BIOS_FILE;
		goto out;
	}

	if (FLASH_CMD_UPDATE == flash_command)
		ret = pm8001_update_flash(pm8001_ha);
	else
		ret = pm8001_set_nvmd(pm8001_ha);

	release_firmware(pm8001_ha->fw_image);
out:
	kfree(cmd_ptr);

	if (ret)
		return ret;

	pm8001_ha->fw_status = FLASH_OK;
	return count;
}