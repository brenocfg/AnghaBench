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
struct TYPE_2__ {struct ddi_vbt_port_info* ddi_port_info; } ;
struct drm_i915_private {TYPE_1__ vbt; } ;
struct ddi_vbt_port_info {int supports_dp; scalar_t__ alternate_aux_channel; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PORT_NONE ; 
 int get_port_by_aux_ch (struct drm_i915_private*,scalar_t__) ; 
 int /*<<< orphan*/  port_name (int) ; 

__attribute__((used)) static void sanitize_aux_ch(struct drm_i915_private *dev_priv,
			    enum port port)
{
	struct ddi_vbt_port_info *info = &dev_priv->vbt.ddi_port_info[port];
	enum port p;

	if (!info->alternate_aux_channel)
		return;

	p = get_port_by_aux_ch(dev_priv, info->alternate_aux_channel);
	if (p != PORT_NONE) {
		DRM_DEBUG_KMS("port %c trying to use the same AUX CH (0x%x) as port %c, "
			      "disabling port %c DP support\n",
			      port_name(port), info->alternate_aux_channel,
			      port_name(p), port_name(p));

		/*
		 * If we have multiple ports supposedlt sharing the
		 * aux channel, then DP couldn't exist on the shared
		 * port. Otherwise they share the same aux channel
		 * and system couldn't communicate with them separately.
		 *
		 * Give inverse child device order the priority,
		 * last one wins. Yes, there are real machines
		 * (eg. Asrock B250M-HDV) where VBT has both
		 * port A and port E with the same AUX ch and
		 * we must pick port E :(
		 */
		info = &dev_priv->vbt.ddi_port_info[p];

		info->supports_dp = false;
		info->alternate_aux_channel = 0;
	}
}