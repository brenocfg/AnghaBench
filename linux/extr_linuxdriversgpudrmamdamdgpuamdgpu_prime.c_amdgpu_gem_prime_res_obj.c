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
struct reservation_object {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct TYPE_2__ {struct reservation_object* resv; } ;
struct amdgpu_bo {TYPE_1__ tbo; } ;

/* Variables and functions */
 struct amdgpu_bo* gem_to_amdgpu_bo (struct drm_gem_object*) ; 

struct reservation_object *amdgpu_gem_prime_res_obj(struct drm_gem_object *obj)
{
	struct amdgpu_bo *bo = gem_to_amdgpu_bo(obj);

	return bo->tbo.resv;
}