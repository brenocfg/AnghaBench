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
 int /*<<< orphan*/  VIRTIO_BALLOON_F_PAGE_POISON ; 
 int /*<<< orphan*/  VIRTIO_F_IOMMU_PLATFORM ; 
 int /*<<< orphan*/  __virtio_clear_bit (struct virtio_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_poisoning_enabled () ; 

__attribute__((used)) static int virtballoon_validate(struct virtio_device *vdev)
{
	if (!page_poisoning_enabled())
		__virtio_clear_bit(vdev, VIRTIO_BALLOON_F_PAGE_POISON);

	__virtio_clear_bit(vdev, VIRTIO_F_IOMMU_PLATFORM);
	return 0;
}