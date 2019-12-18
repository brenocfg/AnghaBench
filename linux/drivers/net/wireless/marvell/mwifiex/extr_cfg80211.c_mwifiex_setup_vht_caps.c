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
struct mwifiex_private {struct mwifiex_adapter* adapter; } ;
struct mwifiex_adapter {int hw_dot_11ac_mcs_support; int /*<<< orphan*/  hw_dot_11ac_dev_cap; } ;
struct TYPE_2__ {scalar_t__ tx_highest; void* tx_mcs_map; scalar_t__ rx_highest; void* rx_mcs_map; } ;
struct ieee80211_sta_vht_cap {int vht_supported; TYPE_1__ vht_mcs; int /*<<< orphan*/  cap; } ;

/* Variables and functions */
 void* cpu_to_le16 (int) ; 

__attribute__((used)) static void mwifiex_setup_vht_caps(struct ieee80211_sta_vht_cap *vht_info,
				   struct mwifiex_private *priv)
{
	struct mwifiex_adapter *adapter = priv->adapter;

	vht_info->vht_supported = true;

	vht_info->cap = adapter->hw_dot_11ac_dev_cap;
	/* Update MCS support for VHT */
	vht_info->vht_mcs.rx_mcs_map = cpu_to_le16(
				adapter->hw_dot_11ac_mcs_support & 0xFFFF);
	vht_info->vht_mcs.rx_highest = 0;
	vht_info->vht_mcs.tx_mcs_map = cpu_to_le16(
				adapter->hw_dot_11ac_mcs_support >> 16);
	vht_info->vht_mcs.tx_highest = 0;
}