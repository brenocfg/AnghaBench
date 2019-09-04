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
struct TYPE_2__ {struct reservation_object* resv; } ;
struct nouveau_bo {TYPE_1__ bo; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 struct nouveau_bo* nouveau_gem_object (struct drm_gem_object*) ; 

struct reservation_object *nouveau_gem_prime_res_obj(struct drm_gem_object *obj)
{
	struct nouveau_bo *nvbo = nouveau_gem_object(obj);

	return nvbo->bo.resv;
}