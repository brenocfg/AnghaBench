#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sas_ha_struct {struct pm8001_hba_info* lldd_ha; } ;
struct TYPE_5__ {int max_sgl; } ;
struct TYPE_4__ {int max_sgl; } ;
struct TYPE_6__ {TYPE_2__ pm80xx_tbl; TYPE_1__ pm8001_tbl; } ;
struct pm8001_hba_info {scalar_t__ chip_id; TYPE_3__ main_cfg_tbl; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct sas_ha_struct* SHOST_TO_SAS_HA (struct Scsi_Host*) ; 
 scalar_t__ chip_8001 ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t pm8001_ctl_max_sg_list_show(struct device *cdev,
	struct device_attribute *attr, char *buf)
{
	struct Scsi_Host *shost = class_to_shost(cdev);
	struct sas_ha_struct *sha = SHOST_TO_SAS_HA(shost);
	struct pm8001_hba_info *pm8001_ha = sha->lldd_ha;

	if (pm8001_ha->chip_id == chip_8001) {
		return snprintf(buf, PAGE_SIZE, "%04d\n",
			pm8001_ha->main_cfg_tbl.pm8001_tbl.max_sgl & 0x0000FFFF
			);
	} else {
		return snprintf(buf, PAGE_SIZE, "%04d\n",
			pm8001_ha->main_cfg_tbl.pm80xx_tbl.max_sgl & 0x0000FFFF
			);
	}
}