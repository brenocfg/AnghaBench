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
struct TYPE_2__ {int /*<<< orphan*/  vht_supported; } ;
struct ieee80211_sta {int /*<<< orphan*/  addr; TYPE_1__ vht_cap; scalar_t__ drv_priv; } ;
struct ath10k_vif {int /*<<< orphan*/  vdev_id; struct ath10k* ar; } ;
struct ath10k_sta {struct ath10k_vif* arvif; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WMI_FIXED_RATE_NONE ; 
 int /*<<< orphan*/  WMI_PEER_PARAM_FIXED_RATE ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int /*<<< orphan*/ ,int) ; 
 int ath10k_wmi_peer_set_param (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath10k_mac_clr_bitrate_mask_iter(void *data,
					     struct ieee80211_sta *sta)
{
	struct ath10k_vif *arvif = data;
	struct ath10k_sta *arsta = (struct ath10k_sta *)sta->drv_priv;
	struct ath10k *ar = arvif->ar;
	int err;

	/* clear vht peers only */
	if (arsta->arvif != arvif || !sta->vht_cap.vht_supported)
		return;

	err = ath10k_wmi_peer_set_param(ar, arvif->vdev_id, sta->addr,
					WMI_PEER_PARAM_FIXED_RATE,
					WMI_FIXED_RATE_NONE);
	if (err)
		ath10k_warn(ar, "failed to clear STA %pM peer fixed rate: %d\n",
			    sta->addr, err);
}