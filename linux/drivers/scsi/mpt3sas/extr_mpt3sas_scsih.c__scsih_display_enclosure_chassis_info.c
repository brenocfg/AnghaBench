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
typedef  int /*<<< orphan*/  u64 ;
struct scsi_target {int dummy; } ;
struct scsi_device {int dummy; } ;
struct _sas_device {scalar_t__ enclosure_handle; char* connector_name; int /*<<< orphan*/  chassis_slot; scalar_t__ is_chassis_slot_valid; int /*<<< orphan*/  enclosure_level; int /*<<< orphan*/  slot; scalar_t__ enclosure_logical_id; } ;
struct MPT3SAS_ADAPTER {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  ioc_info (struct MPT3SAS_ADAPTER*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*,unsigned long long,...) ; 
 int /*<<< orphan*/  starget_printk (int /*<<< orphan*/ ,struct scsi_target*,char*,unsigned long long,...) ; 

__attribute__((used)) static void
_scsih_display_enclosure_chassis_info(struct MPT3SAS_ADAPTER *ioc,
	struct _sas_device *sas_device, struct scsi_device *sdev,
	struct scsi_target *starget)
{
	if (sdev) {
		if (sas_device->enclosure_handle != 0)
			sdev_printk(KERN_INFO, sdev,
			    "enclosure logical id (0x%016llx), slot(%d) \n",
			    (unsigned long long)
			    sas_device->enclosure_logical_id,
			    sas_device->slot);
		if (sas_device->connector_name[0] != '\0')
			sdev_printk(KERN_INFO, sdev,
			    "enclosure level(0x%04x), connector name( %s)\n",
			    sas_device->enclosure_level,
			    sas_device->connector_name);
		if (sas_device->is_chassis_slot_valid)
			sdev_printk(KERN_INFO, sdev, "chassis slot(0x%04x)\n",
			    sas_device->chassis_slot);
	} else if (starget) {
		if (sas_device->enclosure_handle != 0)
			starget_printk(KERN_INFO, starget,
			    "enclosure logical id(0x%016llx), slot(%d) \n",
			    (unsigned long long)
			    sas_device->enclosure_logical_id,
			    sas_device->slot);
		if (sas_device->connector_name[0] != '\0')
			starget_printk(KERN_INFO, starget,
			    "enclosure level(0x%04x), connector name( %s)\n",
			    sas_device->enclosure_level,
			    sas_device->connector_name);
		if (sas_device->is_chassis_slot_valid)
			starget_printk(KERN_INFO, starget,
			    "chassis slot(0x%04x)\n",
			    sas_device->chassis_slot);
	} else {
		if (sas_device->enclosure_handle != 0)
			ioc_info(ioc, "enclosure logical id(0x%016llx), slot(%d)\n",
				 (u64)sas_device->enclosure_logical_id,
				 sas_device->slot);
		if (sas_device->connector_name[0] != '\0')
			ioc_info(ioc, "enclosure level(0x%04x), connector name( %s)\n",
				 sas_device->enclosure_level,
				 sas_device->connector_name);
		if (sas_device->is_chassis_slot_valid)
			ioc_info(ioc, "chassis slot(0x%04x)\n",
				 sas_device->chassis_slot);
	}
}