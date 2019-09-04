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
struct nouveau_bo {int dummy; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TTM_PL_FLAG_TT ; 
 int nouveau_bo_pin (struct nouveau_bo*,int /*<<< orphan*/ ,int) ; 
 struct nouveau_bo* nouveau_gem_object (struct drm_gem_object*) ; 

int nouveau_gem_prime_pin(struct drm_gem_object *obj)
{
	struct nouveau_bo *nvbo = nouveau_gem_object(obj);
	int ret;

	/* pin buffer into GTT */
	ret = nouveau_bo_pin(nvbo, TTM_PL_FLAG_TT, false);
	if (ret)
		return -EINVAL;

	return 0;
}