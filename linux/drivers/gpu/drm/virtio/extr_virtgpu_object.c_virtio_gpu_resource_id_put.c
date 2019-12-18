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
typedef  scalar_t__ uint32_t ;
struct virtio_gpu_device {int /*<<< orphan*/  resource_ida; } ;

/* Variables and functions */
 int /*<<< orphan*/  ida_free (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void virtio_gpu_resource_id_put(struct virtio_gpu_device *vgdev, uint32_t id)
{
#if 0
	ida_free(&vgdev->resource_ida, id - 1);
#endif
}