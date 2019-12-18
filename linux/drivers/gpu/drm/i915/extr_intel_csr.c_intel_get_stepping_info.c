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
struct stepping_info {int dummy; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct stepping_info*) ; 
 int INTEL_REVID (struct drm_i915_private*) ; 
 scalar_t__ IS_BROXTON (struct drm_i915_private*) ; 
 scalar_t__ IS_ICELAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_SKYLAKE (struct drm_i915_private*) ; 
 struct stepping_info* bxt_stepping_info ; 
 struct stepping_info* icl_stepping_info ; 
 struct stepping_info const no_stepping_info ; 
 struct stepping_info* skl_stepping_info ; 

__attribute__((used)) static const struct stepping_info *
intel_get_stepping_info(struct drm_i915_private *dev_priv)
{
	const struct stepping_info *si;
	unsigned int size;

	if (IS_ICELAKE(dev_priv)) {
		size = ARRAY_SIZE(icl_stepping_info);
		si = icl_stepping_info;
	} else if (IS_SKYLAKE(dev_priv)) {
		size = ARRAY_SIZE(skl_stepping_info);
		si = skl_stepping_info;
	} else if (IS_BROXTON(dev_priv)) {
		size = ARRAY_SIZE(bxt_stepping_info);
		si = bxt_stepping_info;
	} else {
		size = 0;
		si = NULL;
	}

	if (INTEL_REVID(dev_priv) < size)
		return si + INTEL_REVID(dev_priv);

	return &no_stepping_info;
}