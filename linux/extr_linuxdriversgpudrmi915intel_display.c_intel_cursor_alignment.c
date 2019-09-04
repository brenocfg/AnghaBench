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
 scalar_t__ IS_I830 (struct drm_i915_private const*) ; 
 scalar_t__ IS_I845G (struct drm_i915_private const*) ; 
 scalar_t__ IS_I85X (struct drm_i915_private const*) ; 
 scalar_t__ IS_I865G (struct drm_i915_private const*) ; 

__attribute__((used)) static unsigned int intel_cursor_alignment(const struct drm_i915_private *dev_priv)
{
	if (IS_I830(dev_priv))
		return 16 * 1024;
	else if (IS_I85X(dev_priv))
		return 256;
	else if (IS_I845G(dev_priv) || IS_I865G(dev_priv))
		return 32;
	else
		return 4 * 1024;
}