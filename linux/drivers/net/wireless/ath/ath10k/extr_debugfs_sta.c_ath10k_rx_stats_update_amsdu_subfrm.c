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
struct ath10k_sta_tid_stats {int /*<<< orphan*/ * rx_pkt_amsdu; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 size_t ATH10K_AMSDU_SUBFRM_NUM_1 ; 
 size_t ATH10K_AMSDU_SUBFRM_NUM_2 ; 
 size_t ATH10K_AMSDU_SUBFRM_NUM_3 ; 
 size_t ATH10K_AMSDU_SUBFRM_NUM_4 ; 
 size_t ATH10K_AMSDU_SUBFRM_NUM_MORE ; 

__attribute__((used)) static void ath10k_rx_stats_update_amsdu_subfrm(struct ath10k *ar,
						struct ath10k_sta_tid_stats *stats,
						u32 msdu_count)
{
	if (msdu_count == 1)
		stats->rx_pkt_amsdu[ATH10K_AMSDU_SUBFRM_NUM_1]++;
	else if (msdu_count == 2)
		stats->rx_pkt_amsdu[ATH10K_AMSDU_SUBFRM_NUM_2]++;
	else if (msdu_count == 3)
		stats->rx_pkt_amsdu[ATH10K_AMSDU_SUBFRM_NUM_3]++;
	else if (msdu_count == 4)
		stats->rx_pkt_amsdu[ATH10K_AMSDU_SUBFRM_NUM_4]++;
	else if (msdu_count > 4)
		stats->rx_pkt_amsdu[ATH10K_AMSDU_SUBFRM_NUM_MORE]++;
}