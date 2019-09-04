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
struct zpci_dev {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_remove_root_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_stop_root_bus (int /*<<< orphan*/ ) ; 

void zpci_remove_device(struct zpci_dev *zdev)
{
	if (!zdev->bus)
		return;

	pci_stop_root_bus(zdev->bus);
	pci_remove_root_bus(zdev->bus);
}