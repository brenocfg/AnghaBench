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
struct TYPE_2__ {scalar_t__ duplex; int /*<<< orphan*/  speed; scalar_t__ link; } ;
struct xgbe_prv_data {int /*<<< orphan*/  netdev; TYPE_1__ phy; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  xgbe_phy_fc_string (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_phy_speed_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgbe_phy_print_status(struct xgbe_prv_data *pdata)
{
	if (pdata->phy.link)
		netdev_info(pdata->netdev,
			    "Link is Up - %s/%s - flow control %s\n",
			    xgbe_phy_speed_string(pdata->phy.speed),
			    pdata->phy.duplex == DUPLEX_FULL ? "Full" : "Half",
			    xgbe_phy_fc_string(pdata));
	else
		netdev_info(pdata->netdev, "Link is Down\n");
}