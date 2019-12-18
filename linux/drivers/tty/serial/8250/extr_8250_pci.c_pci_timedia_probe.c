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
struct pci_dev {int subsystem_device; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int pci_timedia_probe(struct pci_dev *dev)
{
	/*
	 * Check the third digit of the subdevice ID
	 * (0,2,3,5,6: serial only -- 7,8,9: serial + parallel)
	 */
	if ((dev->subsystem_device & 0x00f0) >= 0x70) {
		dev_info(&dev->dev,
			"ignoring Timedia subdevice %04x for parport_serial\n",
			dev->subsystem_device);
		return -ENODEV;
	}

	return 0;
}