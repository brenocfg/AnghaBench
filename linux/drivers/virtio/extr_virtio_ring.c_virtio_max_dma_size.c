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
struct virtio_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t SIZE_MAX ; 
 size_t dma_max_mapping_size (int /*<<< orphan*/ *) ; 
 scalar_t__ vring_use_dma_api (struct virtio_device*) ; 

size_t virtio_max_dma_size(struct virtio_device *vdev)
{
	size_t max_segment_size = SIZE_MAX;

	if (vring_use_dma_api(vdev))
		max_segment_size = dma_max_mapping_size(&vdev->dev);

	return max_segment_size;
}