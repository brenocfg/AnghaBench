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
struct drm_mm_node {int /*<<< orphan*/  size; } ;
struct drm_i915_private {int /*<<< orphan*/  drm; } ;
struct drm_i915_gem_object {int read_domains; struct drm_mm_node* stolen; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 scalar_t__ HAS_LLC (struct drm_i915_private*) ; 
 unsigned int I915_CACHE_LLC ; 
 unsigned int I915_CACHE_NONE ; 
 int I915_GEM_DOMAIN_CPU ; 
 int I915_GEM_DOMAIN_GTT ; 
 int /*<<< orphan*/  drm_gem_private_object_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct drm_i915_gem_object* i915_gem_object_alloc () ; 
 int /*<<< orphan*/  i915_gem_object_free (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_init (struct drm_i915_gem_object*,int /*<<< orphan*/ *) ; 
 scalar_t__ i915_gem_object_pin_pages (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_set_cache_coherency (struct drm_i915_gem_object*,unsigned int) ; 
 int /*<<< orphan*/  i915_gem_object_stolen_ops ; 

__attribute__((used)) static struct drm_i915_gem_object *
_i915_gem_object_create_stolen(struct drm_i915_private *dev_priv,
			       struct drm_mm_node *stolen)
{
	struct drm_i915_gem_object *obj;
	unsigned int cache_level;

	obj = i915_gem_object_alloc();
	if (obj == NULL)
		return NULL;

	drm_gem_private_object_init(&dev_priv->drm, &obj->base, stolen->size);
	i915_gem_object_init(obj, &i915_gem_object_stolen_ops);

	obj->stolen = stolen;
	obj->read_domains = I915_GEM_DOMAIN_CPU | I915_GEM_DOMAIN_GTT;
	cache_level = HAS_LLC(dev_priv) ? I915_CACHE_LLC : I915_CACHE_NONE;
	i915_gem_object_set_cache_coherency(obj, cache_level);

	if (i915_gem_object_pin_pages(obj))
		goto cleanup;

	return obj;

cleanup:
	i915_gem_object_free(obj);
	return NULL;
}