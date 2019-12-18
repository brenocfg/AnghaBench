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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct drm_i915_private {TYPE_1__ fb_tracking; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_NOTE (char*,int) ; 
 int /*<<< orphan*/  i915_gem_init__mm (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_init__pm (struct drm_i915_private*) ; 
 int i915_gemfs_init (struct drm_i915_private*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int i915_gem_init_early(struct drm_i915_private *dev_priv)
{
	int err;

	i915_gem_init__mm(dev_priv);
	i915_gem_init__pm(dev_priv);

	spin_lock_init(&dev_priv->fb_tracking.lock);

	err = i915_gemfs_init(dev_priv);
	if (err)
		DRM_NOTE("Unable to create a private tmpfs mount, hugepage support will be disabled(%d).\n", err);

	return 0;
}