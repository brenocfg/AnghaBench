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
struct drm_gem_object {int /*<<< orphan*/ * funcs; } ;
struct drm_gem_cma_object {struct drm_gem_object base; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_cma_gem_default_funcs ; 
 struct drm_gem_cma_object* kzalloc (int,int /*<<< orphan*/ ) ; 

struct drm_gem_object *
drm_cma_gem_create_object_default_funcs(struct drm_device *dev, size_t size)
{
	struct drm_gem_cma_object *cma_obj;

	cma_obj = kzalloc(sizeof(*cma_obj), GFP_KERNEL);
	if (!cma_obj)
		return NULL;

	cma_obj->base.funcs = &drm_cma_gem_default_funcs;

	return &cma_obj->base;
}