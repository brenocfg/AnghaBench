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
struct mxs_phy {int /*<<< orphan*/  regmap_anatop; TYPE_1__* data; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int MXS_PHY_DISCONNECT_LINE_WITHOUT_VBUS ; 
 int /*<<< orphan*/  __mxs_phy_disconnect_line (struct mxs_phy*,int) ; 
 int mxs_phy_get_vbus_status (struct mxs_phy*) ; 
 int /*<<< orphan*/  mxs_phy_is_otg_host (struct mxs_phy*) ; 

__attribute__((used)) static void mxs_phy_disconnect_line(struct mxs_phy *mxs_phy, bool on)
{
	bool vbus_is_on = false;

	/* If the SoCs don't need to disconnect line without vbus, quit */
	if (!(mxs_phy->data->flags & MXS_PHY_DISCONNECT_LINE_WITHOUT_VBUS))
		return;

	/* If the SoCs don't have anatop, quit */
	if (!mxs_phy->regmap_anatop)
		return;

	vbus_is_on = mxs_phy_get_vbus_status(mxs_phy);

	if (on && !vbus_is_on && !mxs_phy_is_otg_host(mxs_phy))
		__mxs_phy_disconnect_line(mxs_phy, true);
	else
		__mxs_phy_disconnect_line(mxs_phy, false);

}