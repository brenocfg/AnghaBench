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
struct sta_info {int last_rx_rate; int last_rx_updated; int /*<<< orphan*/ * rx_count; int /*<<< orphan*/  last_rx_signal; int /*<<< orphan*/  last_rx_silence; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr2; } ;
struct hostap_80211_rx_status {int rate; int /*<<< orphan*/  signal; int /*<<< orphan*/  noise; } ;
struct ap_data {int /*<<< orphan*/  sta_table_lock; } ;

/* Variables and functions */
 int IW_QUAL_ALL_UPDATED ; 
 int IW_QUAL_DBM ; 
 struct sta_info* ap_get_sta (struct ap_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int hostap_update_rx_stats(struct ap_data *ap,
			   struct ieee80211_hdr *hdr,
			   struct hostap_80211_rx_status *rx_stats)
{
	struct sta_info *sta;

	if (!ap)
		return -1;

	spin_lock(&ap->sta_table_lock);
	sta = ap_get_sta(ap, hdr->addr2);
	if (sta) {
		sta->last_rx_silence = rx_stats->noise;
		sta->last_rx_signal = rx_stats->signal;
		sta->last_rx_rate = rx_stats->rate;
		sta->last_rx_updated = IW_QUAL_ALL_UPDATED | IW_QUAL_DBM;
		if (rx_stats->rate == 10)
			sta->rx_count[0]++;
		else if (rx_stats->rate == 20)
			sta->rx_count[1]++;
		else if (rx_stats->rate == 55)
			sta->rx_count[2]++;
		else if (rx_stats->rate == 110)
			sta->rx_count[3]++;
	}
	spin_unlock(&ap->sta_table_lock);

	return sta ? 0 : -1;
}