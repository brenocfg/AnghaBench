#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  timelines; } ;
struct TYPE_4__ {int object_count; int /*<<< orphan*/  free_count; int /*<<< orphan*/  free_list; } ;
struct drm_i915_private {int /*<<< orphan*/  objects; int /*<<< orphan*/  vmas; int /*<<< orphan*/  luts; int /*<<< orphan*/  requests; int /*<<< orphan*/  dependencies; int /*<<< orphan*/  priorities; TYPE_1__ gt; TYPE_2__ mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_drain_freed_objects (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gemfs_fini (struct drm_i915_private*) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  llist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_barrier () ; 

void i915_gem_cleanup_early(struct drm_i915_private *dev_priv)
{
	i915_gem_drain_freed_objects(dev_priv);
	GEM_BUG_ON(!llist_empty(&dev_priv->mm.free_list));
	GEM_BUG_ON(atomic_read(&dev_priv->mm.free_count));
	WARN_ON(dev_priv->mm.object_count);
	WARN_ON(!list_empty(&dev_priv->gt.timelines));

	kmem_cache_destroy(dev_priv->priorities);
	kmem_cache_destroy(dev_priv->dependencies);
	kmem_cache_destroy(dev_priv->requests);
	kmem_cache_destroy(dev_priv->luts);
	kmem_cache_destroy(dev_priv->vmas);
	kmem_cache_destroy(dev_priv->objects);

	/* And ensure that our DESTROY_BY_RCU slabs are truly destroyed */
	rcu_barrier();

	i915_gemfs_fini(dev_priv);
}