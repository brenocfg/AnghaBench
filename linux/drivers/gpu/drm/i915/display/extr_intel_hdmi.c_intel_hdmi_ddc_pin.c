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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {struct ddi_vbt_port_info* ddi_port_info; } ;
struct drm_i915_private {TYPE_1__ vbt; } ;
struct ddi_vbt_port_info {scalar_t__ alternate_ddc_pin; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ HAS_PCH_CNP (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_ICP (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_MCC (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_TGP (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 scalar_t__ bxt_port_to_ddc_pin (struct drm_i915_private*,int) ; 
 scalar_t__ chv_port_to_ddc_pin (struct drm_i915_private*,int) ; 
 scalar_t__ cnp_port_to_ddc_pin (struct drm_i915_private*,int) ; 
 scalar_t__ g4x_port_to_ddc_pin (struct drm_i915_private*,int) ; 
 scalar_t__ icl_port_to_ddc_pin (struct drm_i915_private*,int) ; 
 scalar_t__ mcc_port_to_ddc_pin (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  port_name (int) ; 

__attribute__((used)) static u8 intel_hdmi_ddc_pin(struct drm_i915_private *dev_priv,
			     enum port port)
{
	const struct ddi_vbt_port_info *info =
		&dev_priv->vbt.ddi_port_info[port];
	u8 ddc_pin;

	if (info->alternate_ddc_pin) {
		DRM_DEBUG_KMS("Using DDC pin 0x%x for port %c (VBT)\n",
			      info->alternate_ddc_pin, port_name(port));
		return info->alternate_ddc_pin;
	}

	if (HAS_PCH_MCC(dev_priv))
		ddc_pin = mcc_port_to_ddc_pin(dev_priv, port);
	else if (HAS_PCH_TGP(dev_priv) || HAS_PCH_ICP(dev_priv))
		ddc_pin = icl_port_to_ddc_pin(dev_priv, port);
	else if (HAS_PCH_CNP(dev_priv))
		ddc_pin = cnp_port_to_ddc_pin(dev_priv, port);
	else if (IS_GEN9_LP(dev_priv))
		ddc_pin = bxt_port_to_ddc_pin(dev_priv, port);
	else if (IS_CHERRYVIEW(dev_priv))
		ddc_pin = chv_port_to_ddc_pin(dev_priv, port);
	else
		ddc_pin = g4x_port_to_ddc_pin(dev_priv, port);

	DRM_DEBUG_KMS("Using DDC pin 0x%x for port %c (platform default)\n",
		      ddc_pin, port_name(port));

	return ddc_pin;
}