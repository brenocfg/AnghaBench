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
struct pqi_scsi_dev {int devtype; int /*<<< orphan*/  scsi3addr; scalar_t__ is_expander_smp_device; } ;

/* Variables and functions */
#define  TYPE_DISK 133 
#define  TYPE_ENCLOSURE 132 
#define  TYPE_MEDIUM_CHANGER 131 
#define  TYPE_RAID 130 
#define  TYPE_TAPE 129 
#define  TYPE_ZBC 128 
 int /*<<< orphan*/  pqi_is_hba_lunid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool pqi_is_supported_device(struct pqi_scsi_dev *device)
{
	bool is_supported;

	if (device->is_expander_smp_device)
		return true;

	is_supported = false;

	switch (device->devtype) {
	case TYPE_DISK:
	case TYPE_ZBC:
	case TYPE_TAPE:
	case TYPE_MEDIUM_CHANGER:
	case TYPE_ENCLOSURE:
		is_supported = true;
		break;
	case TYPE_RAID:
		/*
		 * Only support the HBA controller itself as a RAID
		 * controller.  If it's a RAID controller other than
		 * the HBA itself (an external RAID controller, for
		 * example), we don't support it.
		 */
		if (pqi_is_hba_lunid(device->scsi3addr))
			is_supported = true;
		break;
	}

	return is_supported;
}