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
struct TYPE_2__ {int /*<<< orphan*/  asle; } ;
struct drm_i915_private {TYPE_1__ opregion; } ;

/* Variables and functions */
 scalar_t__ IS_MOBILE (struct drm_i915_private*) ; 
 scalar_t__ IS_PINEVIEW (struct drm_i915_private*) ; 

__attribute__((used)) static bool i915_has_asle(struct drm_i915_private *dev_priv)
{
	if (!dev_priv->opregion.asle)
		return false;

	return IS_PINEVIEW(dev_priv) || IS_MOBILE(dev_priv);
}