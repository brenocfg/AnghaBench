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
struct virtio_gpu_device {int /*<<< orphan*/ * vbufs; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ *) ; 

void virtio_gpu_free_vbufs(struct virtio_gpu_device *vgdev)
{
	kmem_cache_destroy(vgdev->vbufs);
	vgdev->vbufs = NULL;
}