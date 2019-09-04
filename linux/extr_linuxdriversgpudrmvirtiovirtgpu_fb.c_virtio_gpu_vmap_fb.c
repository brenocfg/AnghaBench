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
struct virtio_gpu_object {int dummy; } ;
struct virtio_gpu_device {int dummy; } ;

/* Variables and functions */
 int virtio_gpu_object_kmap (struct virtio_gpu_object*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int virtio_gpu_vmap_fb(struct virtio_gpu_device *vgdev,
			      struct virtio_gpu_object *obj)
{
	return virtio_gpu_object_kmap(obj, NULL);
}