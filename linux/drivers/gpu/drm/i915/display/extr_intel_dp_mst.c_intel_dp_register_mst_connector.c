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
struct drm_i915_private {TYPE_1__* fbdev; } ;
struct drm_connector {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  helper; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_connector_register (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_fb_helper_add_one_connector (int /*<<< orphan*/ *,struct drm_connector*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_dp_register_mst_connector(struct drm_connector *connector)
{
	struct drm_i915_private *dev_priv = to_i915(connector->dev);

	if (dev_priv->fbdev)
		drm_fb_helper_add_one_connector(&dev_priv->fbdev->helper,
						connector);

	drm_connector_register(connector);
}