#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct virtio_device {TYPE_1__ dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_ALIGN (size_t) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,size_t,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pages_exact (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ vring_use_dma_api (struct virtio_device*) ; 

__attribute__((used)) static void vring_free_queue(struct virtio_device *vdev, size_t size,
			     void *queue, dma_addr_t dma_handle)
{
	if (vring_use_dma_api(vdev))
		dma_free_coherent(vdev->dev.parent, size, queue, dma_handle);
	else
		free_pages_exact(queue, PAGE_ALIGN(size));
}