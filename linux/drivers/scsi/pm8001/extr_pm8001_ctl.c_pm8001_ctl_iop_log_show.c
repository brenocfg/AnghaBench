#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sas_ha_struct {struct pm8001_hba_info* lldd_ha; } ;
struct TYPE_8__ {TYPE_3__* region; } ;
struct TYPE_5__ {int event_log_size; } ;
struct TYPE_6__ {TYPE_1__ pm80xx_tbl; } ;
struct pm8001_hba_info {TYPE_4__ memoryMap; TYPE_2__ main_cfg_tbl; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_7__ {scalar_t__ virt_ptr; } ;

/* Variables and functions */
 size_t IOP ; 
 struct sas_ha_struct* SHOST_TO_SAS_HA (struct Scsi_Host*) ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t pm8001_ctl_iop_log_show(struct device *cdev,
	struct device_attribute *attr, char *buf)
{
	struct Scsi_Host *shost = class_to_shost(cdev);
	struct sas_ha_struct *sha = SHOST_TO_SAS_HA(shost);
	struct pm8001_hba_info *pm8001_ha = sha->lldd_ha;
	char *str = buf;
	u32 read_size =
		pm8001_ha->main_cfg_tbl.pm80xx_tbl.event_log_size / 1024;
	static u32 start, end, count;
	u32 max_read_times = 32;
	u32 max_count = (read_size * 1024) / (max_read_times * 4);
	u32 *temp = (u32 *)pm8001_ha->memoryMap.region[IOP].virt_ptr;

	if ((count % max_count) == 0) {
		start = 0;
		end = max_read_times;
		count = 0;
	} else {
		start = end;
		end = end + max_read_times;
	}

	for (; start < end; start++)
		str += sprintf(str, "%08x ", *(temp+start));
	count++;
	return str - buf;
}