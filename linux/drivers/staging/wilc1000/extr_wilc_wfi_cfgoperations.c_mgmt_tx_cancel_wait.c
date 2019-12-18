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
typedef  int /*<<< orphan*/  u64 ;
struct wireless_dev {int /*<<< orphan*/  netdev; } ;
struct wiphy {int dummy; } ;
struct wilc_wfi_p2p_listen_params {int /*<<< orphan*/  listen_ch; int /*<<< orphan*/  listen_cookie; } ;
struct wilc_priv {struct wilc_wfi_p2p_listen_params remain_on_ch_params; int /*<<< orphan*/  p2p_listen_state; struct host_if_drv* hif_drv; } ;
struct wilc_vif {struct wilc_priv priv; } ;
struct host_if_drv {int /*<<< orphan*/  p2p_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cfg80211_remain_on_channel_expired (struct wireless_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 struct wilc_vif* netdev_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mgmt_tx_cancel_wait(struct wiphy *wiphy,
			       struct wireless_dev *wdev,
			       u64 cookie)
{
	struct wilc_vif *vif = netdev_priv(wdev->netdev);
	struct wilc_priv *priv = &vif->priv;
	struct host_if_drv *wfi_drv = priv->hif_drv;

	wfi_drv->p2p_timeout = jiffies;

	if (!priv->p2p_listen_state) {
		struct wilc_wfi_p2p_listen_params *params;

		params = &priv->remain_on_ch_params;

		cfg80211_remain_on_channel_expired(wdev,
						   params->listen_cookie,
						   params->listen_ch,
						   GFP_KERNEL);
	}

	return 0;
}