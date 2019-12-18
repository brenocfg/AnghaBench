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
struct virtio_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  virtio_has_iommu_quirk (struct virtio_device*) ; 
 scalar_t__ xen_domain () ; 

__attribute__((used)) static bool vring_use_dma_api(struct virtio_device *vdev)
{
	if (!virtio_has_iommu_quirk(vdev))
		return true;

	/* Otherwise, we are left to guess. */
	/*
	 * In theory, it's possible to have a buggy QEMU-supposed
	 * emulated Q35 IOMMU and Xen enabled at the same time.  On
	 * such a configuration, virtio has never worked and will
	 * not work without an even larger kludge.  Instead, enable
	 * the DMA API if we're a Xen guest, which at least allows
	 * all of the sensible Xen configurations to work correctly.
	 */
	if (xen_domain())
		return true;

	return false;
}