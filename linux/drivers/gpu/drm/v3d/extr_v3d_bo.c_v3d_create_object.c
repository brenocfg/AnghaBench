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
struct drm_gem_object {int /*<<< orphan*/ * funcs; } ;
struct TYPE_2__ {struct drm_gem_object base; } ;
struct v3d_bo {TYPE_1__ base; int /*<<< orphan*/  unref_head; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct v3d_bo* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v3d_gem_funcs ; 

struct drm_gem_object *v3d_create_object(struct drm_device *dev, size_t size)
{
	struct v3d_bo *bo;
	struct drm_gem_object *obj;

	if (size == 0)
		return NULL;

	bo = kzalloc(sizeof(*bo), GFP_KERNEL);
	if (!bo)
		return NULL;
	obj = &bo->base.base;

	obj->funcs = &v3d_gem_funcs;

	INIT_LIST_HEAD(&bo->unref_head);

	return &bo->base.base;
}