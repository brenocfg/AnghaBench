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
typedef  int u8 ;
struct sas_ha_struct {struct pm8001_hba_info* lldd_ha; } ;
struct TYPE_3__ {int inc_fw_version; } ;
struct TYPE_4__ {TYPE_1__ pm80xx_tbl; } ;
struct pm8001_hba_info {scalar_t__ chip_id; TYPE_2__ main_cfg_tbl; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct sas_ha_struct* SHOST_TO_SAS_HA (struct Scsi_Host*) ; 
 scalar_t__ chip_8001 ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int,int,int,int) ; 

__attribute__((used)) static ssize_t pm8001_ctl_inactive_fw_version_show(struct device *cdev,
	struct device_attribute *attr, char *buf)
{
	struct Scsi_Host *shost = class_to_shost(cdev);
	struct sas_ha_struct *sha = SHOST_TO_SAS_HA(shost);
	struct pm8001_hba_info *pm8001_ha = sha->lldd_ha;

	if (pm8001_ha->chip_id != chip_8001) {
		return snprintf(buf, PAGE_SIZE, "%02x.%02x.%02x.%02x\n",
		(u8)(pm8001_ha->main_cfg_tbl.pm80xx_tbl.inc_fw_version >> 24),
		(u8)(pm8001_ha->main_cfg_tbl.pm80xx_tbl.inc_fw_version >> 16),
		(u8)(pm8001_ha->main_cfg_tbl.pm80xx_tbl.inc_fw_version >> 8),
		(u8)(pm8001_ha->main_cfg_tbl.pm80xx_tbl.inc_fw_version));
	}
	return 0;
}