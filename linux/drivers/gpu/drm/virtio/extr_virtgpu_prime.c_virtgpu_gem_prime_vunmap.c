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
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gem_to_virtio_gpu_obj (struct drm_gem_object*) ; 
 int /*<<< orphan*/  virtio_gpu_object_kunmap (int /*<<< orphan*/ ) ; 

void virtgpu_gem_prime_vunmap(struct drm_gem_object *obj, void *vaddr)
{
	virtio_gpu_object_kunmap(gem_to_virtio_gpu_obj(obj));
}