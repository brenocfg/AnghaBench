#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pqi_ctrl_info {char* serial_number; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 struct pqi_ctrl_info* shost_to_hba (struct Scsi_Host*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static ssize_t pqi_serial_number_show(struct device *dev,
	struct device_attribute *attr, char *buffer)
{
	struct Scsi_Host *shost;
	struct pqi_ctrl_info *ctrl_info;

	shost = class_to_shost(dev);
	ctrl_info = shost_to_hba(shost);

	return snprintf(buffer, PAGE_SIZE, "%s\n", ctrl_info->serial_number);
}