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
struct pqi_scsi_dev {int devtype; scalar_t__ is_expander_smp_device; int /*<<< orphan*/  is_physical_device; } ;

/* Variables and functions */
#define  TYPE_DISK 130 
#define  TYPE_ENCLOSURE 129 
#define  TYPE_ZBC 128 

__attribute__((used)) static inline bool pqi_is_device_with_sas_address(struct pqi_scsi_dev *device)
{
	if (!device->is_physical_device)
		return false;

	if (device->is_expander_smp_device)
		return true;

	switch (device->devtype) {
	case TYPE_DISK:
	case TYPE_ZBC:
	case TYPE_ENCLOSURE:
		return true;
	}

	return false;
}