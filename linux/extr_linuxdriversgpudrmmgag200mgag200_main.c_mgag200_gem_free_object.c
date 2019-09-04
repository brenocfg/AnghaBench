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
struct mgag200_bo {int dummy; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 struct mgag200_bo* gem_to_mga_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  mgag200_bo_unref (struct mgag200_bo**) ; 

void mgag200_gem_free_object(struct drm_gem_object *obj)
{
	struct mgag200_bo *mgag200_bo = gem_to_mga_bo(obj);

	mgag200_bo_unref(&mgag200_bo);
}