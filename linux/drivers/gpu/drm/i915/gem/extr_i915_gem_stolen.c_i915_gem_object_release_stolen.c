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
struct drm_i915_private {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct drm_i915_gem_object {int /*<<< orphan*/  stolen; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 struct drm_mm_node* fetch_and_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_stolen_remove_node (struct drm_i915_private*,struct drm_mm_node*) ; 
 int /*<<< orphan*/  kfree (struct drm_mm_node*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
i915_gem_object_release_stolen(struct drm_i915_gem_object *obj)
{
	struct drm_i915_private *dev_priv = to_i915(obj->base.dev);
	struct drm_mm_node *stolen = fetch_and_zero(&obj->stolen);

	GEM_BUG_ON(!stolen);

	i915_gem_stolen_remove_node(dev_priv, stolen);
	kfree(stolen);
}