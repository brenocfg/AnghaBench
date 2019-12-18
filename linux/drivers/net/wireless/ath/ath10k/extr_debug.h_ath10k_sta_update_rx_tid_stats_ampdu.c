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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct htt_rx_indication_mpdu_range {int dummy; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline
void ath10k_sta_update_rx_tid_stats_ampdu(struct ath10k *ar,
					  u16 peer_id, u8 tid,
					  struct htt_rx_indication_mpdu_range *ranges,
					  int num_ranges)
{
}