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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct drm_i915_private {int hdcp_comp_added; int /*<<< orphan*/  hdcp_comp_mutex; TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 int /*<<< orphan*/  I915_COMPONENT_HDCP ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int component_add_typed (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_hdcp_component_ops ; 
 int /*<<< orphan*/  is_hdcp2_supported (struct drm_i915_private*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void intel_hdcp_component_init(struct drm_i915_private *dev_priv)
{
	int ret;

	if (!is_hdcp2_supported(dev_priv))
		return;

	mutex_lock(&dev_priv->hdcp_comp_mutex);
	WARN_ON(dev_priv->hdcp_comp_added);

	dev_priv->hdcp_comp_added = true;
	mutex_unlock(&dev_priv->hdcp_comp_mutex);
	ret = component_add_typed(dev_priv->drm.dev, &i915_hdcp_component_ops,
				  I915_COMPONENT_HDCP);
	if (ret < 0) {
		DRM_DEBUG_KMS("Failed at component add(%d)\n", ret);
		mutex_lock(&dev_priv->hdcp_comp_mutex);
		dev_priv->hdcp_comp_added = false;
		mutex_unlock(&dev_priv->hdcp_comp_mutex);
		return;
	}
}