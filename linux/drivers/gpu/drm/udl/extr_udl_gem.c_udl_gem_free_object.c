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
struct udl_gem_object {scalar_t__ pages; int /*<<< orphan*/  sg; scalar_t__ vmapping; } ;
struct drm_gem_object {TYPE_1__* dev; scalar_t__ import_attach; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_gem_free_mmap_offset (struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_prime_gem_destroy (struct drm_gem_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ ) ; 
 struct udl_gem_object* to_udl_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  udl_gem_put_pages (struct udl_gem_object*) ; 
 int /*<<< orphan*/  udl_gem_vunmap (struct udl_gem_object*) ; 

void udl_gem_free_object(struct drm_gem_object *gem_obj)
{
	struct udl_gem_object *obj = to_udl_bo(gem_obj);

	if (obj->vmapping)
		udl_gem_vunmap(obj);

	if (gem_obj->import_attach) {
		drm_prime_gem_destroy(gem_obj, obj->sg);
		put_device(gem_obj->dev->dev);
	}

	if (obj->pages)
		udl_gem_put_pages(obj);

	drm_gem_free_mmap_offset(gem_obj);
}