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
struct myrs_hba {TYPE_1__* ctlr_info; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int fw_major_version; int fw_minor_version; int fw_turn_number; } ;

/* Variables and functions */
 struct Scsi_Host* class_to_shost (struct device*) ; 
 struct myrs_hba* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int) ; 

__attribute__((used)) static ssize_t firmware_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct Scsi_Host *shost = class_to_shost(dev);
	struct myrs_hba *cs = shost_priv(shost);

	return snprintf(buf, 16, "%d.%02d-%02d\n",
			cs->ctlr_info->fw_major_version,
			cs->ctlr_info->fw_minor_version,
			cs->ctlr_info->fw_turn_number);
}