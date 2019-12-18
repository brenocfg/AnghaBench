#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct wireless_dev {scalar_t__ iftype; int /*<<< orphan*/  netdev; } ;
struct wiphy {int dummy; } ;
struct TYPE_5__ {unsigned int listen_duration; scalar_t__ listen_cookie; struct ieee80211_channel* listen_ch; } ;
struct wilc_priv {scalar_t__ inc_roc_cookie; int p2p_listen_state; TYPE_2__ remain_on_ch_params; } ;
struct wilc_vif {TYPE_3__* hif_drv; TYPE_1__* wilc; int /*<<< orphan*/  ndev; struct wilc_priv priv; } ;
struct ieee80211_channel {int /*<<< orphan*/  hw_value; } ;
struct TYPE_6__ {int /*<<< orphan*/  remain_on_ch_timer; } ;
struct TYPE_4__ {int /*<<< orphan*/  op_ch; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  cfg80211_ready_on_channel (struct wireless_dev*,scalar_t__,struct ieee80211_channel*,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (unsigned int) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct wilc_vif* netdev_priv (int /*<<< orphan*/ ) ; 
 int wilc_remain_on_channel (struct wilc_vif*,scalar_t__,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  wilc_wfi_remain_on_channel_expired ; 

__attribute__((used)) static int remain_on_channel(struct wiphy *wiphy,
			     struct wireless_dev *wdev,
			     struct ieee80211_channel *chan,
			     unsigned int duration, u64 *cookie)
{
	int ret = 0;
	struct wilc_vif *vif = netdev_priv(wdev->netdev);
	struct wilc_priv *priv = &vif->priv;
	u64 id;

	if (wdev->iftype == NL80211_IFTYPE_AP) {
		netdev_dbg(vif->ndev, "Required while in AP mode\n");
		return ret;
	}

	id = ++priv->inc_roc_cookie;
	if (id == 0)
		id = ++priv->inc_roc_cookie;

	ret = wilc_remain_on_channel(vif, id, duration, chan->hw_value,
				     wilc_wfi_remain_on_channel_expired,
				     (void *)vif);
	if (ret)
		return ret;

	vif->wilc->op_ch = chan->hw_value;

	priv->remain_on_ch_params.listen_ch = chan;
	priv->remain_on_ch_params.listen_cookie = id;
	*cookie = id;
	priv->p2p_listen_state = true;
	priv->remain_on_ch_params.listen_duration = duration;

	cfg80211_ready_on_channel(wdev, *cookie, chan, duration, GFP_KERNEL);
	mod_timer(&vif->hif_drv->remain_on_ch_timer,
		  jiffies + msecs_to_jiffies(duration));

	return ret;
}