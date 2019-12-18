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
typedef  scalar_t__ u64 ;
struct wireless_dev {int /*<<< orphan*/  netdev; } ;
struct wiphy {int dummy; } ;
struct mwifiex_roc_cfg {int dummy; } ;
struct TYPE_2__ {scalar_t__ cookie; int /*<<< orphan*/  chan; } ;
struct mwifiex_private {int /*<<< orphan*/  adapter; TYPE_1__ roc_cfg; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  HostCmd_ACT_GEN_REMOVE ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  cfg80211_remain_on_channel_expired (struct wireless_dev*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mwifiex_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 struct mwifiex_private* mwifiex_netdev_get_priv (int /*<<< orphan*/ ) ; 
 int mwifiex_remain_on_chan_cfg (struct mwifiex_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mwifiex_cfg80211_cancel_remain_on_channel(struct wiphy *wiphy,
					  struct wireless_dev *wdev, u64 cookie)
{
	struct mwifiex_private *priv = mwifiex_netdev_get_priv(wdev->netdev);
	int ret;

	if (cookie != priv->roc_cfg.cookie)
		return -ENOENT;

	ret = mwifiex_remain_on_chan_cfg(priv, HostCmd_ACT_GEN_REMOVE,
					 &priv->roc_cfg.chan, 0);

	if (!ret) {
		cfg80211_remain_on_channel_expired(wdev, cookie,
						   &priv->roc_cfg.chan,
						   GFP_ATOMIC);

		memset(&priv->roc_cfg, 0, sizeof(struct mwifiex_roc_cfg));

		mwifiex_dbg(priv->adapter, INFO,
			    "info: cancel ROC, cookie = 0x%llx\n", cookie);
	}

	return ret;
}