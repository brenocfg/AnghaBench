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
typedef  scalar_t__ u8 ;
struct vfio_pci_device {scalar_t__* pci_config_map; } ;
typedef  size_t loff_t ;

/* Variables and functions */

__attribute__((used)) static size_t vfio_pci_cap_remaining_dword(struct vfio_pci_device *vdev,
					   loff_t pos)
{
	u8 cap = vdev->pci_config_map[pos];
	size_t i;

	for (i = 1; (pos + i) % 4 && vdev->pci_config_map[pos + i] == cap; i++)
		/* nop */;

	return i;
}