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
struct etnaviv_gem_object {int /*<<< orphan*/  lock; } ;
struct drm_gem_object {int /*<<< orphan*/  import_attach; } ;

/* Variables and functions */
 int /*<<< orphan*/  etnaviv_gem_put_pages (struct etnaviv_gem_object*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct etnaviv_gem_object* to_etnaviv_bo (struct drm_gem_object*) ; 

void etnaviv_gem_prime_unpin(struct drm_gem_object *obj)
{
	if (!obj->import_attach) {
		struct etnaviv_gem_object *etnaviv_obj = to_etnaviv_bo(obj);

		mutex_lock(&etnaviv_obj->lock);
		etnaviv_gem_put_pages(to_etnaviv_bo(obj));
		mutex_unlock(&etnaviv_obj->lock);
	}
}