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
typedef  int u32 ;
struct wiphy {int dummy; } ;
struct net_device {int dummy; } ;
struct mwifiex_private {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  mwifiex_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int mwifiex_drv_set_power (struct mwifiex_private*,int*) ; 
 struct mwifiex_private* mwifiex_netdev_get_priv (struct net_device*) ; 

__attribute__((used)) static int
mwifiex_cfg80211_set_power_mgmt(struct wiphy *wiphy,
				struct net_device *dev,
				bool enabled, int timeout)
{
	struct mwifiex_private *priv = mwifiex_netdev_get_priv(dev);
	u32 ps_mode;

	if (timeout)
		mwifiex_dbg(priv->adapter, INFO,
			    "info: ignore timeout value for IEEE Power Save\n");

	ps_mode = enabled;

	return mwifiex_drv_set_power(priv, &ps_mode);
}