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
struct drm_i915_private {int /*<<< orphan*/  hdcp_comp_mutex; int /*<<< orphan*/ * hdcp_master; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 struct drm_i915_private* kdev_to_i915 (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i915_hdcp_component_unbind(struct device *i915_kdev,
				       struct device *mei_kdev, void *data)
{
	struct drm_i915_private *dev_priv = kdev_to_i915(i915_kdev);

	DRM_DEBUG("I915 HDCP comp unbind\n");
	mutex_lock(&dev_priv->hdcp_comp_mutex);
	dev_priv->hdcp_master = NULL;
	mutex_unlock(&dev_priv->hdcp_comp_mutex);
}