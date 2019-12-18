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
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_channel_io_perm_failure ; 
 int /*<<< orphan*/  pci_dev_set_io_state (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int pci_dev_set_disconnected(struct pci_dev *dev, void *unused)
{
	device_lock(&dev->dev);
	pci_dev_set_io_state(dev, pci_channel_io_perm_failure);
	device_unlock(&dev->dev);

	return 0;
}