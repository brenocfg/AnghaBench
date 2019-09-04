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
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int ARRAY_SIZE (struct ddi_buf_trans const*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_COFFEELAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_KABYLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_SKYLAKE (struct drm_i915_private*) ; 
 struct ddi_buf_trans const* bdw_ddi_translations_dp ; 
 struct ddi_buf_trans const* hsw_ddi_translations_dp ; 
 struct ddi_buf_trans* kbl_get_buf_trans_dp (struct drm_i915_private*,int*) ; 
 int skl_buf_trans_num_entries (int,int) ; 
 struct ddi_buf_trans* skl_get_buf_trans_dp (struct drm_i915_private*,int*) ; 

__attribute__((used)) static const struct ddi_buf_trans *
intel_ddi_get_buf_trans_dp(struct drm_i915_private *dev_priv,
			   enum port port, int *n_entries)
{
	if (IS_KABYLAKE(dev_priv) || IS_COFFEELAKE(dev_priv)) {
		const struct ddi_buf_trans *ddi_translations =
			kbl_get_buf_trans_dp(dev_priv, n_entries);
		*n_entries = skl_buf_trans_num_entries(port, *n_entries);
		return ddi_translations;
	} else if (IS_SKYLAKE(dev_priv)) {
		const struct ddi_buf_trans *ddi_translations =
			skl_get_buf_trans_dp(dev_priv, n_entries);
		*n_entries = skl_buf_trans_num_entries(port, *n_entries);
		return ddi_translations;
	} else if (IS_BROADWELL(dev_priv)) {
		*n_entries = ARRAY_SIZE(bdw_ddi_translations_dp);
		return  bdw_ddi_translations_dp;
	} else if (IS_HASWELL(dev_priv)) {
		*n_entries = ARRAY_SIZE(hsw_ddi_translations_dp);
		return hsw_ddi_translations_dp;
	}

	*n_entries = 0;
	return NULL;
}