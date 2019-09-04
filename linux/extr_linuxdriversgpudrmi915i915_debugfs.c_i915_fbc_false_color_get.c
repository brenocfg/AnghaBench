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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  false_color; } ;
struct drm_i915_private {TYPE_1__ fbc; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  HAS_FBC (struct drm_i915_private*) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 

__attribute__((used)) static int i915_fbc_false_color_get(void *data, u64 *val)
{
	struct drm_i915_private *dev_priv = data;

	if (INTEL_GEN(dev_priv) < 7 || !HAS_FBC(dev_priv))
		return -ENODEV;

	*val = dev_priv->fbc.false_color;

	return 0;
}