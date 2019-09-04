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
struct i40e_pf {int dummy; } ;
struct i40e_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_UNKNOWN ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 
 int /*<<< orphan*/  i40e_phy_type_to_ethtool (struct i40e_pf*,struct ethtool_link_ksettings*) ; 

__attribute__((used)) static void i40e_get_settings_link_down(struct i40e_hw *hw,
					struct ethtool_link_ksettings *ks,
					struct i40e_pf *pf)
{
	/* link is down and the driver needs to fall back on
	 * supported phy types to figure out what info to display
	 */
	i40e_phy_type_to_ethtool(pf, ks);

	/* With no link speed and duplex are unknown */
	ks->base.speed = SPEED_UNKNOWN;
	ks->base.duplex = DUPLEX_UNKNOWN;
}