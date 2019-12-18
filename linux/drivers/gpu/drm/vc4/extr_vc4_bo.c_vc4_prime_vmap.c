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
struct vc4_bo {scalar_t__ validated_shader; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  EINVAL ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 void* drm_gem_cma_prime_vmap (struct drm_gem_object*) ; 
 struct vc4_bo* to_vc4_bo (struct drm_gem_object*) ; 

void *vc4_prime_vmap(struct drm_gem_object *obj)
{
	struct vc4_bo *bo = to_vc4_bo(obj);

	if (bo->validated_shader) {
		DRM_DEBUG("mmaping of shader BOs not allowed.\n");
		return ERR_PTR(-EINVAL);
	}

	return drm_gem_cma_prime_vmap(obj);
}