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
struct virtio_gpu_object_params {int dummy; } ;
struct virtio_gpu_object {int dummy; } ;
struct virtio_gpu_fence {int dummy; } ;
struct virtio_gpu_device {int dummy; } ;
struct drm_device {struct virtio_gpu_device* dev_private; } ;

/* Variables and functions */
 struct virtio_gpu_object* ERR_PTR (int) ; 
 int virtio_gpu_object_create (struct virtio_gpu_device*,struct virtio_gpu_object_params*,struct virtio_gpu_object**,struct virtio_gpu_fence*) ; 

struct virtio_gpu_object*
virtio_gpu_alloc_object(struct drm_device *dev,
			struct virtio_gpu_object_params *params,
			struct virtio_gpu_fence *fence)
{
	struct virtio_gpu_device *vgdev = dev->dev_private;
	struct virtio_gpu_object *obj;
	int ret;

	ret = virtio_gpu_object_create(vgdev, params, &obj, fence);
	if (ret)
		return ERR_PTR(ret);

	return obj;
}