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
struct ethtool_link_ksettings {int dummy; } ;
struct TYPE_2__ {struct ethtool_link_ksettings lks; } ;
struct xgbe_prv_data {TYPE_1__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XGBE_LM_COPY (struct ethtool_link_ksettings*,int /*<<< orphan*/ ,struct ethtool_link_ksettings*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  advertising ; 

__attribute__((used)) static void xgbe_phy_an_advertising(struct xgbe_prv_data *pdata,
				    struct ethtool_link_ksettings *dlks)
{
	struct ethtool_link_ksettings *slks = &pdata->phy.lks;

	XGBE_LM_COPY(dlks, advertising, slks, advertising);
}