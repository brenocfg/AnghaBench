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
struct sk_buff {int /*<<< orphan*/  ip_summed; } ;
struct iwl_mvm_vif {int features; } ;
struct iwl_mvm_sta {int /*<<< orphan*/  vif; } ;
struct ieee80211_sta {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int NETIF_F_RXCSUM ; 
 int RX_MPDU_RES_STATUS_CSUM_DONE ; 
 int RX_MPDU_RES_STATUS_CSUM_OK ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_mvm_rx_csum(struct ieee80211_sta *sta,
			    struct sk_buff *skb,
			    u32 status)
{
	struct iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(mvmsta->vif);

	if (mvmvif->features & NETIF_F_RXCSUM &&
	    status & RX_MPDU_RES_STATUS_CSUM_DONE &&
	    status & RX_MPDU_RES_STATUS_CSUM_OK)
		skb->ip_summed = CHECKSUM_UNNECESSARY;
}