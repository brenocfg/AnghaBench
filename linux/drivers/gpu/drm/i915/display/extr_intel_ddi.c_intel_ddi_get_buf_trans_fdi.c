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
struct ddi_buf_trans {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct ddi_buf_trans const*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 struct ddi_buf_trans const* bdw_ddi_translations_fdi ; 
 struct ddi_buf_trans const* hsw_ddi_translations_fdi ; 

__attribute__((used)) static const struct ddi_buf_trans *
intel_ddi_get_buf_trans_fdi(struct drm_i915_private *dev_priv,
			    int *n_entries)
{
	if (IS_BROADWELL(dev_priv)) {
		*n_entries = ARRAY_SIZE(bdw_ddi_translations_fdi);
		return bdw_ddi_translations_fdi;
	} else if (IS_HASWELL(dev_priv)) {
		*n_entries = ARRAY_SIZE(hsw_ddi_translations_fdi);
		return hsw_ddi_translations_fdi;
	}

	*n_entries = 0;
	return NULL;
}