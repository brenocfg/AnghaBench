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
struct mac80211_hwsim_data {int /*<<< orphan*/  group; int /*<<< orphan*/  ps; int /*<<< orphan*/  tx_failed; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_pkts; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_pkts; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct mac80211_hwsim_data* priv; } ;
struct ethtool_stats {int dummy; } ;

/* Variables and functions */
 int MAC80211_HWSIM_SSTATS_LEN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static void mac80211_hwsim_get_et_stats(struct ieee80211_hw *hw,
					struct ieee80211_vif *vif,
					struct ethtool_stats *stats, u64 *data)
{
	struct mac80211_hwsim_data *ar = hw->priv;
	int i = 0;

	data[i++] = ar->tx_pkts;
	data[i++] = ar->tx_bytes;
	data[i++] = ar->rx_pkts;
	data[i++] = ar->rx_bytes;
	data[i++] = ar->tx_dropped;
	data[i++] = ar->tx_failed;
	data[i++] = ar->ps;
	data[i++] = ar->group;

	WARN_ON(i != MAC80211_HWSIM_SSTATS_LEN);
}