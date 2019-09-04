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
struct hibmc_bo {int dummy; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 struct hibmc_bo* gem_to_hibmc_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  hibmc_bo_unref (struct hibmc_bo**) ; 

void hibmc_gem_free_object(struct drm_gem_object *obj)
{
	struct hibmc_bo *hibmcbo = gem_to_hibmc_bo(obj);

	hibmc_bo_unref(&hibmcbo);
}