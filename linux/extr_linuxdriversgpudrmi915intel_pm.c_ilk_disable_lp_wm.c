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
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM_DIRTY_LP_ALL ; 
 int _ilk_disable_lp_wm (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

bool ilk_disable_lp_wm(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = to_i915(dev);

	return _ilk_disable_lp_wm(dev_priv, WM_DIRTY_LP_ALL);
}