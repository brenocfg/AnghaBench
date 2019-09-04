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
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 struct virtio_gpu_object* gem_to_virtio_gpu_obj (struct drm_gem_object*) ; 
 int /*<<< orphan*/  virtio_gpu_object_unref (struct virtio_gpu_object**) ; 

void virtio_gpu_gem_free_object(struct drm_gem_object *gem_obj)
{
	struct virtio_gpu_object *obj = gem_to_virtio_gpu_obj(gem_obj);

	if (obj)
		virtio_gpu_object_unref(&obj);
}