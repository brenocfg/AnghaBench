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
struct reservation_object {int dummy; } ;
struct msm_gem_object {struct reservation_object* resv; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 struct msm_gem_object* to_msm_bo (struct drm_gem_object*) ; 

struct reservation_object *msm_gem_prime_res_obj(struct drm_gem_object *obj)
{
	struct msm_gem_object *msm_obj = to_msm_bo(obj);

	return msm_obj->resv;
}