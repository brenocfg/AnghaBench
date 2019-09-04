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
struct drm_mm_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  stolen; } ;
struct drm_i915_private {TYPE_1__ mm; } ;
struct drm_i915_gem_object {int dummy; } ;
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct drm_i915_gem_object* _i915_gem_object_create_stolen (struct drm_i915_private*,struct drm_mm_node*) ; 
 int /*<<< orphan*/  drm_mm_initialized (int /*<<< orphan*/ *) ; 
 int i915_gem_stolen_insert_node (struct drm_i915_private*,struct drm_mm_node*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i915_gem_stolen_remove_node (struct drm_i915_private*,struct drm_mm_node*) ; 
 int /*<<< orphan*/  kfree (struct drm_mm_node*) ; 
 struct drm_mm_node* kzalloc (int,int /*<<< orphan*/ ) ; 

struct drm_i915_gem_object *
i915_gem_object_create_stolen(struct drm_i915_private *dev_priv,
			      resource_size_t size)
{
	struct drm_i915_gem_object *obj;
	struct drm_mm_node *stolen;
	int ret;

	if (!drm_mm_initialized(&dev_priv->mm.stolen))
		return NULL;

	if (size == 0)
		return NULL;

	stolen = kzalloc(sizeof(*stolen), GFP_KERNEL);
	if (!stolen)
		return NULL;

	ret = i915_gem_stolen_insert_node(dev_priv, stolen, size, 4096);
	if (ret) {
		kfree(stolen);
		return NULL;
	}

	obj = _i915_gem_object_create_stolen(dev_priv, stolen);
	if (obj)
		return obj;

	i915_gem_stolen_remove_node(dev_priv, stolen);
	kfree(stolen);
	return NULL;
}