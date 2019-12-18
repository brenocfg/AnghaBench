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
typedef  int u64 ;
struct wireless_dev {int /*<<< orphan*/  netdev; } ;
struct wiphy {int dummy; } ;
struct ieee80211_channel {int dummy; } ;
struct TYPE_2__ {int cookie; struct ieee80211_channel chan; } ;
struct mwifiex_private {int /*<<< orphan*/  adapter; TYPE_1__ roc_cfg; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  HostCmd_ACT_GEN_SET ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  cfg80211_ready_on_channel (struct wireless_dev*,int,struct ieee80211_channel*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 struct mwifiex_private* mwifiex_netdev_get_priv (int /*<<< orphan*/ ) ; 
 int mwifiex_remain_on_chan_cfg (struct mwifiex_private*,int /*<<< orphan*/ ,struct ieee80211_channel*,unsigned int) ; 
 int prandom_u32 () ; 

__attribute__((used)) static int
mwifiex_cfg80211_remain_on_channel(struct wiphy *wiphy,
				   struct wireless_dev *wdev,
				   struct ieee80211_channel *chan,
				   unsigned int duration, u64 *cookie)
{
	struct mwifiex_private *priv = mwifiex_netdev_get_priv(wdev->netdev);
	int ret;

	if (!chan || !cookie) {
		mwifiex_dbg(priv->adapter, ERROR, "Invalid parameter for ROC\n");
		return -EINVAL;
	}

	if (priv->roc_cfg.cookie) {
		mwifiex_dbg(priv->adapter, INFO,
			    "info: ongoing ROC, cookie = 0x%llx\n",
			    priv->roc_cfg.cookie);
		return -EBUSY;
	}

	ret = mwifiex_remain_on_chan_cfg(priv, HostCmd_ACT_GEN_SET, chan,
					 duration);

	if (!ret) {
		*cookie = prandom_u32() | 1;
		priv->roc_cfg.cookie = *cookie;
		priv->roc_cfg.chan = *chan;

		cfg80211_ready_on_channel(wdev, *cookie, chan,
					  duration, GFP_ATOMIC);

		mwifiex_dbg(priv->adapter, INFO,
			    "info: ROC, cookie = 0x%llx\n", *cookie);
	}

	return ret;
}