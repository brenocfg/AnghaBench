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
struct pci_dev {int error_state; int /*<<< orphan*/  dev; } ;
typedef  int pci_channel_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  device_lock_assert (int /*<<< orphan*/ *) ; 
#define  pci_channel_io_frozen 130 
#define  pci_channel_io_normal 129 
#define  pci_channel_io_perm_failure 128 

__attribute__((used)) static inline bool pci_dev_set_io_state(struct pci_dev *dev,
					pci_channel_state_t new)
{
	bool changed = false;

	device_lock_assert(&dev->dev);
	switch (new) {
	case pci_channel_io_perm_failure:
		switch (dev->error_state) {
		case pci_channel_io_frozen:
		case pci_channel_io_normal:
		case pci_channel_io_perm_failure:
			changed = true;
			break;
		}
		break;
	case pci_channel_io_frozen:
		switch (dev->error_state) {
		case pci_channel_io_frozen:
		case pci_channel_io_normal:
			changed = true;
			break;
		}
		break;
	case pci_channel_io_normal:
		switch (dev->error_state) {
		case pci_channel_io_frozen:
		case pci_channel_io_normal:
			changed = true;
			break;
		}
		break;
	}
	if (changed)
		dev->error_state = new;
	return changed;
}