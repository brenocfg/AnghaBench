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
struct sk_buff_head {int dummy; } ;
struct ieee80211_rx_status {int /*<<< orphan*/  freq; } ;
struct ath10k {int /*<<< orphan*/  dev_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_CAC_RUNNING ; 
 int /*<<< orphan*/  ATH10K_DBG_HTT ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ath10k_htt_rx_amsdu_allowed(struct ath10k *ar,
					struct sk_buff_head *amsdu,
					struct ieee80211_rx_status *rx_status)
{
	/* FIXME: It might be a good idea to do some fuzzy-testing to drop
	 * invalid/dangerous frames.
	 */

	if (!rx_status->freq) {
		ath10k_dbg(ar, ATH10K_DBG_HTT, "no channel configured; ignoring frame(s)!\n");
		return false;
	}

	if (test_bit(ATH10K_CAC_RUNNING, &ar->dev_flags)) {
		ath10k_dbg(ar, ATH10K_DBG_HTT, "htt rx cac running\n");
		return false;
	}

	return true;
}