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
struct sis_laptop {scalar_t__ device; scalar_t__ subvendor; scalar_t__ subdevice; } ;
struct pci_dev {scalar_t__ device; scalar_t__ subsystem_vendor; scalar_t__ subsystem_device; } ;

/* Variables and functions */
 struct sis_laptop* sis_laptop ; 

__attribute__((used)) static int sis_short_ata40(struct pci_dev *dev)
{
	const struct sis_laptop *lap = &sis_laptop[0];

	while (lap->device) {
		if (lap->device == dev->device &&
		    lap->subvendor == dev->subsystem_vendor &&
		    lap->subdevice == dev->subsystem_device)
			return 1;
		lap++;
	}

	return 0;
}