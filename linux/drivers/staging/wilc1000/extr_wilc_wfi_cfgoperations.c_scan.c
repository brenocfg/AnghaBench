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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct wiphy {int dummy; } ;
struct wilc_priv {int cfg_scanning; struct cfg80211_scan_request* scan_req; } ;
struct wilc_vif {int /*<<< orphan*/  ndev; struct wilc_priv priv; } ;
struct cfg80211_scan_request {int n_channels; scalar_t__ n_ssids; TYPE_2__** channels; TYPE_1__* wdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  center_freq; } ;
struct TYPE_3__ {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WILC_FW_ACTIVE_SCAN ; 
 int /*<<< orphan*/  WILC_FW_PASSIVE_SCAN ; 
 int /*<<< orphan*/  WILC_FW_USER_SCAN ; 
 int WILC_MAX_NUM_SCANNED_CH ; 
 int /*<<< orphan*/  cfg_scan_result ; 
 int /*<<< orphan*/  ieee80211_frequency_to_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 struct wilc_vif* netdev_priv (int /*<<< orphan*/ ) ; 
 int wilc_scan (struct wilc_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,void*,struct cfg80211_scan_request*) ; 

__attribute__((used)) static int scan(struct wiphy *wiphy, struct cfg80211_scan_request *request)
{
	struct wilc_vif *vif = netdev_priv(request->wdev->netdev);
	struct wilc_priv *priv = &vif->priv;
	u32 i;
	int ret = 0;
	u8 scan_ch_list[WILC_MAX_NUM_SCANNED_CH];
	u8 scan_type;

	if (request->n_channels > WILC_MAX_NUM_SCANNED_CH) {
		netdev_err(vif->ndev, "Requested scanned channels over\n");
		return -EINVAL;
	}

	priv->scan_req = request;
	priv->cfg_scanning = true;
	for (i = 0; i < request->n_channels; i++) {
		u16 freq = request->channels[i]->center_freq;

		scan_ch_list[i] = ieee80211_frequency_to_channel(freq);
	}

	if (request->n_ssids)
		scan_type = WILC_FW_ACTIVE_SCAN;
	else
		scan_type = WILC_FW_PASSIVE_SCAN;

	ret = wilc_scan(vif, WILC_FW_USER_SCAN, scan_type, scan_ch_list,
			request->n_channels, cfg_scan_result, (void *)priv,
			request);

	if (ret) {
		priv->scan_req = NULL;
		priv->cfg_scanning = false;
	}

	return ret;
}