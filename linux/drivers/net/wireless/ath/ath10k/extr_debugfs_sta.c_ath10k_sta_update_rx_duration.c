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
struct ath10k_fw_stats {scalar_t__ extended; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath10k_sta_update_extd_stats_rx_duration (struct ath10k*,struct ath10k_fw_stats*) ; 
 int /*<<< orphan*/  ath10k_sta_update_stats_rx_duration (struct ath10k*,struct ath10k_fw_stats*) ; 

void ath10k_sta_update_rx_duration(struct ath10k *ar,
				   struct ath10k_fw_stats *stats)
{
	if (stats->extended)
		ath10k_sta_update_extd_stats_rx_duration(ar, stats);
	else
		ath10k_sta_update_stats_rx_duration(ar, stats);
}