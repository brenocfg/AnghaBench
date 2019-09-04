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
struct drm_vgem_gem_object {int /*<<< orphan*/  table; int /*<<< orphan*/  pages_lock; int /*<<< orphan*/  pages; } ;
struct drm_gem_object {scalar_t__ import_attach; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_gem_object_release (struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_prime_gem_destroy (struct drm_gem_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct drm_vgem_gem_object*) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct drm_vgem_gem_object* to_vgem_bo (struct drm_gem_object*) ; 

__attribute__((used)) static void vgem_gem_free_object(struct drm_gem_object *obj)
{
	struct drm_vgem_gem_object *vgem_obj = to_vgem_bo(obj);

	kvfree(vgem_obj->pages);
	mutex_destroy(&vgem_obj->pages_lock);

	if (obj->import_attach)
		drm_prime_gem_destroy(obj, vgem_obj->table);

	drm_gem_object_release(obj);
	kfree(vgem_obj);
}