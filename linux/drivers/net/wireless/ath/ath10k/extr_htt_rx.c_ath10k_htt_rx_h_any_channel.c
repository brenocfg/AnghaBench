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
struct ieee80211_channel {int dummy; } ;
struct cfg80211_chan_def {struct ieee80211_channel* chan; } ;
struct ath10k {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath10k_htt_rx_h_any_chan_iter ; 
 int /*<<< orphan*/  ieee80211_iter_chan_contexts_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cfg80211_chan_def*) ; 

__attribute__((used)) static struct ieee80211_channel *
ath10k_htt_rx_h_any_channel(struct ath10k *ar)
{
	struct cfg80211_chan_def def = {};

	ieee80211_iter_chan_contexts_atomic(ar->hw,
					    ath10k_htt_rx_h_any_chan_iter,
					    &def);

	return def.chan;
}