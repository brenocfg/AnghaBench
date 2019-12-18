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
struct drm_i915_private {int /*<<< orphan*/  runtime_pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_runtime_pm_put_unchecked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void mmio_hw_access_post(struct drm_i915_private *dev_priv)
{
	intel_runtime_pm_put_unchecked(&dev_priv->runtime_pm);
}