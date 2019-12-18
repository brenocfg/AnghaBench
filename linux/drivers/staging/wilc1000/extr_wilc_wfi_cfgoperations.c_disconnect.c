#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct wiphy {int dummy; } ;
struct TYPE_3__ {int local_random; int recv_random; int is_wilc_ie; } ;
struct wilc_priv {int /*<<< orphan*/  dev; TYPE_2__* hif_drv; TYPE_1__ p2p; } ;
struct wilc_vif {int connecting; scalar_t__ iftype; struct wilc* wilc; struct wilc_priv priv; } ;
struct wilc {int /*<<< orphan*/  sta_ch; scalar_t__ close; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ p2p_timeout; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WILC_CLIENT_MODE ; 
 int /*<<< orphan*/  WILC_INVALID_CHANNEL ; 
 int /*<<< orphan*/  WILC_STATION_MODE ; 
 int /*<<< orphan*/  cfg80211_disconnected (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 
 int wilc_disconnect (struct wilc_vif*) ; 
 int /*<<< orphan*/  wilc_wlan_set_bssid (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int disconnect(struct wiphy *wiphy, struct net_device *dev,
		      u16 reason_code)
{
	struct wilc_vif *vif = netdev_priv(dev);
	struct wilc_priv *priv = &vif->priv;
	struct wilc *wilc = vif->wilc;
	int ret;

	vif->connecting = false;

	if (!wilc)
		return -EIO;

	if (wilc->close) {
		/* already disconnected done */
		cfg80211_disconnected(dev, 0, NULL, 0, true, GFP_KERNEL);
		return 0;
	}

	if (vif->iftype != WILC_CLIENT_MODE)
		wilc->sta_ch = WILC_INVALID_CHANNEL;
	wilc_wlan_set_bssid(priv->dev, NULL, WILC_STATION_MODE);

	priv->p2p.local_random = 0x01;
	priv->p2p.recv_random = 0x00;
	priv->p2p.is_wilc_ie = false;
	priv->hif_drv->p2p_timeout = 0;

	ret = wilc_disconnect(vif);
	if (ret != 0) {
		netdev_err(priv->dev, "Error in disconnecting\n");
		ret = -EINVAL;
	}

	return ret;
}