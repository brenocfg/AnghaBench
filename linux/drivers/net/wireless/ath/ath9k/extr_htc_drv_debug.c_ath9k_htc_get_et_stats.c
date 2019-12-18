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
typedef  int /*<<< orphan*/  u64 ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct ath9k_htc_priv* priv; } ;
struct ethtool_stats {int dummy; } ;
struct ath9k_htc_priv {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  skb_completed_bytes; int /*<<< orphan*/  skb_completed; } ;
struct TYPE_5__ {int /*<<< orphan*/  skb_success_bytes; int /*<<< orphan*/  skb_success; } ;
struct TYPE_4__ {int /*<<< orphan*/ * phy_err_stats; int /*<<< orphan*/  decrypt_busy_err; int /*<<< orphan*/  post_delim_crc_err; int /*<<< orphan*/  pre_delim_crc_err; int /*<<< orphan*/  mic_err; int /*<<< orphan*/  phy_err; int /*<<< orphan*/  decrypt_crc_err; int /*<<< orphan*/  crc_err; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASTXQ (int /*<<< orphan*/ ) ; 
 int ATH9K_HTC_SSTATS_LEN ; 
 size_t ATH9K_PHYERR_CCK_TIMING ; 
 size_t ATH9K_PHYERR_OFDM_TIMING ; 
 size_t ATH9K_PHYERR_RADAR ; 
 TYPE_3__ SKBRXBASE ; 
 TYPE_2__ SKBTXBASE ; 
 TYPE_1__ SRXBASE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  queue_stats ; 

void ath9k_htc_get_et_stats(struct ieee80211_hw *hw,
			    struct ieee80211_vif *vif,
			    struct ethtool_stats *stats, u64 *data)
{
	struct ath9k_htc_priv *priv = hw->priv;
	int i = 0;

	data[i++] = SKBTXBASE.skb_success;
	data[i++] = SKBTXBASE.skb_success_bytes;
	data[i++] = SKBRXBASE.skb_completed;
	data[i++] = SKBRXBASE.skb_completed_bytes;

	ASTXQ(queue_stats);

	data[i++] = SRXBASE.crc_err;
	data[i++] = SRXBASE.decrypt_crc_err;
	data[i++] = SRXBASE.phy_err;
	data[i++] = SRXBASE.mic_err;
	data[i++] = SRXBASE.pre_delim_crc_err;
	data[i++] = SRXBASE.post_delim_crc_err;
	data[i++] = SRXBASE.decrypt_busy_err;

	data[i++] = SRXBASE.phy_err_stats[ATH9K_PHYERR_RADAR];
	data[i++] = SRXBASE.phy_err_stats[ATH9K_PHYERR_OFDM_TIMING];
	data[i++] = SRXBASE.phy_err_stats[ATH9K_PHYERR_CCK_TIMING];

	WARN_ON(i != ATH9K_HTC_SSTATS_LEN);
}