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
 scalar_t__ IS_SKL_ULT (struct drm_i915_private*) ; 
 scalar_t__ IS_SKL_ULX (struct drm_i915_private*) ; 
 struct ddi_buf_trans const* skl_ddi_translations_dp ; 
 struct ddi_buf_trans const* skl_u_ddi_translations_dp ; 
 struct ddi_buf_trans const* skl_y_ddi_translations_dp ; 

__attribute__((used)) static const struct ddi_buf_trans *
skl_get_buf_trans_dp(struct drm_i915_private *dev_priv, int *n_entries)
{
	if (IS_SKL_ULX(dev_priv)) {
		*n_entries = ARRAY_SIZE(skl_y_ddi_translations_dp);
		return skl_y_ddi_translations_dp;
	} else if (IS_SKL_ULT(dev_priv)) {
		*n_entries = ARRAY_SIZE(skl_u_ddi_translations_dp);
		return skl_u_ddi_translations_dp;
	} else {
		*n_entries = ARRAY_SIZE(skl_ddi_translations_dp);
		return skl_ddi_translations_dp;
	}
}