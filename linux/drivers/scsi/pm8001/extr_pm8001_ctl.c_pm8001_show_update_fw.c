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
struct pm8001_hba_info {scalar_t__ fw_status; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {scalar_t__ err_code; char* reason; } ;

/* Variables and functions */
 scalar_t__ FLASH_IN_PROGRESS ; 
 scalar_t__ FLASH_OK ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct sas_ha_struct* SHOST_TO_SAS_HA (struct Scsi_Host*) ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 TYPE_1__* flash_error_table ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,scalar_t__,char*) ; 

__attribute__((used)) static ssize_t pm8001_show_update_fw(struct device *cdev,
				     struct device_attribute *attr, char *buf)
{
	int i;
	struct Scsi_Host *shost = class_to_shost(cdev);
	struct sas_ha_struct *sha = SHOST_TO_SAS_HA(shost);
	struct pm8001_hba_info *pm8001_ha = sha->lldd_ha;

	for (i = 0; flash_error_table[i].err_code != 0; i++) {
		if (flash_error_table[i].err_code == pm8001_ha->fw_status)
			break;
	}
	if (pm8001_ha->fw_status != FLASH_IN_PROGRESS)
		pm8001_ha->fw_status = FLASH_OK;

	return snprintf(buf, PAGE_SIZE, "status=%x %s\n",
			flash_error_table[i].err_code,
			flash_error_table[i].reason);
}