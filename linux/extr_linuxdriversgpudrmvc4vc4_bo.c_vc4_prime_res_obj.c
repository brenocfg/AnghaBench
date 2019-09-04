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
struct vc4_bo {struct reservation_object* resv; } ;
struct reservation_object {int dummy; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 struct vc4_bo* to_vc4_bo (struct drm_gem_object*) ; 

struct reservation_object *vc4_prime_res_obj(struct drm_gem_object *obj)
{
	struct vc4_bo *bo = to_vc4_bo(obj);

	return bo->resv;
}