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
struct drm_gem_object {int /*<<< orphan*/  vma_node; struct drm_device* dev; } ;
struct drm_file {int dummy; } ;
struct drm_device {TYPE_1__* driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* gem_close_object ) (struct drm_gem_object*,struct drm_file*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_PRIME ; 
 scalar_t__ drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_handle_put_unlocked (struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_gem_remove_prime_handles (struct drm_gem_object*,struct drm_file*) ; 
 int /*<<< orphan*/  drm_vma_node_revoke (int /*<<< orphan*/ *,struct drm_file*) ; 
 int /*<<< orphan*/  stub1 (struct drm_gem_object*,struct drm_file*) ; 

__attribute__((used)) static int
drm_gem_object_release_handle(int id, void *ptr, void *data)
{
	struct drm_file *file_priv = data;
	struct drm_gem_object *obj = ptr;
	struct drm_device *dev = obj->dev;

	if (dev->driver->gem_close_object)
		dev->driver->gem_close_object(obj, file_priv);

	if (drm_core_check_feature(dev, DRIVER_PRIME))
		drm_gem_remove_prime_handles(obj, file_priv);
	drm_vma_node_revoke(&obj->vma_node, file_priv);

	drm_gem_object_handle_put_unlocked(obj);

	return 0;
}