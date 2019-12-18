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
typedef  int /*<<< orphan*/  u8 ;
struct wiphy {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  wep_enabled; } ;
struct mwifiex_private {scalar_t__ bss_type; int /*<<< orphan*/  adapter; int /*<<< orphan*/  wep_key_curr_index; TYPE_1__ sec_info; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ MWIFIEX_BSS_TYPE_UAP ; 
 int /*<<< orphan*/  mwifiex_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct mwifiex_private* mwifiex_netdev_get_priv (struct net_device*) ; 
 scalar_t__ mwifiex_set_encode (struct mwifiex_private*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mwifiex_cfg80211_set_default_key(struct wiphy *wiphy, struct net_device *netdev,
				 u8 key_index, bool unicast,
				 bool multicast)
{
	struct mwifiex_private *priv = mwifiex_netdev_get_priv(netdev);

	/* Return if WEP key not configured */
	if (!priv->sec_info.wep_enabled)
		return 0;

	if (priv->bss_type == MWIFIEX_BSS_TYPE_UAP) {
		priv->wep_key_curr_index = key_index;
	} else if (mwifiex_set_encode(priv, NULL, NULL, 0, key_index,
				      NULL, 0)) {
		mwifiex_dbg(priv->adapter, ERROR, "set default Tx key index\n");
		return -EFAULT;
	}

	return 0;
}