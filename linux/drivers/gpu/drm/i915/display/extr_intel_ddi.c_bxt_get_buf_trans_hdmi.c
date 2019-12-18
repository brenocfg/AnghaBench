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
struct bxt_ddi_buf_trans {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct bxt_ddi_buf_trans const*) ; 
 struct bxt_ddi_buf_trans const* bxt_ddi_translations_hdmi ; 

__attribute__((used)) static const struct bxt_ddi_buf_trans *
bxt_get_buf_trans_hdmi(struct drm_i915_private *dev_priv, int *n_entries)
{
	*n_entries = ARRAY_SIZE(bxt_ddi_translations_hdmi);
	return bxt_ddi_translations_hdmi;
}