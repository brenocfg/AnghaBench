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
struct intel_crtc {int dummy; } ;
struct drm_i915_private {struct intel_crtc** plane_to_crtc_mapping; } ;
typedef  enum i9xx_plane_id { ____Placeholder_i9xx_plane_id } i9xx_plane_id ;

/* Variables and functions */

__attribute__((used)) static inline struct intel_crtc *
intel_get_crtc_for_plane(struct drm_i915_private *dev_priv, enum i9xx_plane_id plane)
{
	return dev_priv->plane_to_crtc_mapping[plane];
}