#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ieee80211_supported_band {int n_bitrates; TYPE_6__* bitrates; } ;
struct ieee80211_sta {int* supp_rates; } ;
struct ieee80211_bss_conf {int basic_rates; int /*<<< orphan*/  bssid; } ;
struct ar5523_cmd_rateset {int* set; int length; } ;
struct ar5523 {TYPE_5__* hw; int /*<<< orphan*/  vif; } ;
struct TYPE_12__ {int hw_value; } ;
struct TYPE_9__ {TYPE_2__* chan; } ;
struct TYPE_10__ {TYPE_3__ chandef; } ;
struct TYPE_11__ {TYPE_4__ conf; TYPE_1__* wiphy; } ;
struct TYPE_8__ {size_t band; } ;
struct TYPE_7__ {struct ieee80211_supported_band** bands; } ;

/* Variables and functions */
 int AR5523_MAX_NRATES ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ar5523_dbg (struct ar5523*,char*,int,...) ; 
 int /*<<< orphan*/  ar5523_info (struct ar5523*,char*) ; 
 struct ieee80211_sta* ieee80211_find_sta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ar5523_create_rateset(struct ar5523 *ar,
				  struct ieee80211_bss_conf *bss_conf,
				  struct ar5523_cmd_rateset *rs,
				  bool basic)
{
	struct ieee80211_supported_band *band;
	struct ieee80211_sta *sta;
	int bit, i = 0;
	u32 sta_rate_set, basic_rate_set;

	sta = ieee80211_find_sta(ar->vif, bss_conf->bssid);
	basic_rate_set = bss_conf->basic_rates;
	if (!sta) {
		ar5523_info(ar, "STA not found. Cannot set rates\n");
		sta_rate_set = bss_conf->basic_rates;
	} else
		sta_rate_set = sta->supp_rates[ar->hw->conf.chandef.chan->band];

	ar5523_dbg(ar, "sta rate_set = %08x\n", sta_rate_set);

	band = ar->hw->wiphy->bands[ar->hw->conf.chandef.chan->band];
	for (bit = 0; bit < band->n_bitrates; bit++) {
		BUG_ON(i >= AR5523_MAX_NRATES);
		ar5523_dbg(ar, "Considering rate %d : %d\n",
			   band->bitrates[bit].hw_value, sta_rate_set & 1);
		if (sta_rate_set & 1) {
			rs->set[i] = band->bitrates[bit].hw_value;
			if (basic_rate_set & 1 && basic)
				rs->set[i] |= 0x80;
			i++;
		}
		sta_rate_set >>= 1;
		basic_rate_set >>= 1;
	}

	rs->length = i;
}