#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int cxsr; } ;
struct TYPE_4__ {int cxsr; } ;
struct TYPE_6__ {int /*<<< orphan*/  wm_mutex; TYPE_2__ g4x; TYPE_1__ vlv; } ;
struct drm_i915_private {TYPE_3__ wm; } ;

/* Variables and functions */
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_G4X (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int _intel_set_memory_cxsr (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

bool intel_set_memory_cxsr(struct drm_i915_private *dev_priv, bool enable)
{
	bool ret;

	mutex_lock(&dev_priv->wm.wm_mutex);
	ret = _intel_set_memory_cxsr(dev_priv, enable);
	if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		dev_priv->wm.vlv.cxsr = enable;
	else if (IS_G4X(dev_priv))
		dev_priv->wm.g4x.cxsr = enable;
	mutex_unlock(&dev_priv->wm.wm_mutex);

	return ret;
}