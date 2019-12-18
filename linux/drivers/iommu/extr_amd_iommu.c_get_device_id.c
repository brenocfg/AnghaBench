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
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ dev_is_pci (struct device*) ; 
 int get_acpihid_device_id (struct device*,int /*<<< orphan*/ *) ; 
 int get_pci_device_id (struct device*) ; 

__attribute__((used)) static inline int get_device_id(struct device *dev)
{
	int devid;

	if (dev_is_pci(dev))
		devid = get_pci_device_id(dev);
	else
		devid = get_acpihid_device_id(dev, NULL);

	return devid;
}