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
struct etnaviv_vram_mapping {scalar_t__ use; struct etnaviv_gem_object* object; } ;
struct etnaviv_gem_object {int /*<<< orphan*/  base; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void etnaviv_gem_mapping_unreference(struct etnaviv_vram_mapping *mapping)
{
	struct etnaviv_gem_object *etnaviv_obj = mapping->object;

	mutex_lock(&etnaviv_obj->lock);
	WARN_ON(mapping->use == 0);
	mapping->use -= 1;
	mutex_unlock(&etnaviv_obj->lock);

	drm_gem_object_put_unlocked(&etnaviv_obj->base);
}