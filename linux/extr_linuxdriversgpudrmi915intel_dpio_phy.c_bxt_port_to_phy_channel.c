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
struct drm_i915_private {int dummy; } ;
struct bxt_ddi_phy_info {TYPE_1__* channel; scalar_t__ dual_channel; } ;
typedef  enum port { ____Placeholder_port } port ;
typedef  enum dpio_phy { ____Placeholder_dpio_phy } dpio_phy ;
typedef  enum dpio_channel { ____Placeholder_dpio_channel } dpio_channel ;
struct TYPE_2__ {int port; } ;

/* Variables and functions */
 size_t DPIO_CH0 ; 
 size_t DPIO_CH1 ; 
 int DPIO_PHY0 ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ) ; 
 struct bxt_ddi_phy_info* bxt_get_phy_list (struct drm_i915_private*,int*) ; 
 int /*<<< orphan*/  port_name (int) ; 

void bxt_port_to_phy_channel(struct drm_i915_private *dev_priv, enum port port,
			     enum dpio_phy *phy, enum dpio_channel *ch)
{
	const struct bxt_ddi_phy_info *phy_info, *phys;
	int i, count;

	phys = bxt_get_phy_list(dev_priv, &count);

	for (i = 0; i < count; i++) {
		phy_info = &phys[i];

		if (port == phy_info->channel[DPIO_CH0].port) {
			*phy = i;
			*ch = DPIO_CH0;
			return;
		}

		if (phy_info->dual_channel &&
		    port == phy_info->channel[DPIO_CH1].port) {
			*phy = i;
			*ch = DPIO_CH1;
			return;
		}
	}

	WARN(1, "PHY not found for PORT %c", port_name(port));
	*phy = DPIO_PHY0;
	*ch = DPIO_CH0;
}