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

/* Variables and functions */
 int /*<<< orphan*/  intel_gvt_sanitize_options (struct drm_i915_private*) ; 

__attribute__((used)) static void intel_sanitize_options(struct drm_i915_private *dev_priv)
{
	intel_gvt_sanitize_options(dev_priv);
}