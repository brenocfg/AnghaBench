#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ low_vswing; } ;
struct TYPE_4__ {TYPE_1__ edp; } ;
struct drm_i915_private {TYPE_2__ vbt; } ;
struct bxt_ddi_buf_trans {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct bxt_ddi_buf_trans const*) ; 
 struct bxt_ddi_buf_trans const* bxt_ddi_translations_edp ; 
 struct bxt_ddi_buf_trans const* bxt_get_buf_trans_dp (struct drm_i915_private*,int*) ; 

__attribute__((used)) static const struct bxt_ddi_buf_trans *
bxt_get_buf_trans_edp(struct drm_i915_private *dev_priv, int *n_entries)
{
	if (dev_priv->vbt.edp.low_vswing) {
		*n_entries = ARRAY_SIZE(bxt_ddi_translations_edp);
		return bxt_ddi_translations_edp;
	}

	return bxt_get_buf_trans_dp(dev_priv, n_entries);
}