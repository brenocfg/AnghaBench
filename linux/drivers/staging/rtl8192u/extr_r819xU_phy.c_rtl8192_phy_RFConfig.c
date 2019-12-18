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
struct r8192_priv {int rf_chip; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_ERR ; 
#define  RF_8256 128 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_rf8256_config (struct net_device*) ; 

void rtl8192_phy_RFConfig(struct net_device *dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);

	switch (priv->rf_chip) {
	case RF_8256:
		phy_rf8256_config(dev);
		break;
	default:
		RT_TRACE(COMP_ERR, "error chip id\n");
		break;
	}
}