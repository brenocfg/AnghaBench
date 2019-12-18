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
struct intel_wm_config {int num_pipes_active; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 unsigned int ilk_cursor_wm_reg_max (struct drm_i915_private const*,int) ; 

__attribute__((used)) static unsigned int ilk_cursor_wm_max(const struct drm_i915_private *dev_priv,
				      int level,
				      const struct intel_wm_config *config)
{
	/* HSW LP1+ watermarks w/ multiple pipes */
	if (level > 0 && config->num_pipes_active > 1)
		return 64;

	/* otherwise just report max that registers can hold */
	return ilk_cursor_wm_reg_max(dev_priv, level);
}