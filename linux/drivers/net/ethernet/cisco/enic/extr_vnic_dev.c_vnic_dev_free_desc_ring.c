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
struct vnic_dev_ring {int /*<<< orphan*/ * descs; int /*<<< orphan*/  base_addr_unaligned; int /*<<< orphan*/  descs_unaligned; int /*<<< orphan*/  size_unaligned; } ;
struct vnic_dev {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vnic_dev_free_desc_ring(struct vnic_dev *vdev, struct vnic_dev_ring *ring)
{
	if (ring->descs) {
		pci_free_consistent(vdev->pdev,
			ring->size_unaligned,
			ring->descs_unaligned,
			ring->base_addr_unaligned);
		ring->descs = NULL;
	}
}