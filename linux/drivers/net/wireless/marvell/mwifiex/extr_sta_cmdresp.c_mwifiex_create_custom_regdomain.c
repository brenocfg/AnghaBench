#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct mwifiex_private {int dummy; } ;
struct ieee80211_regdomain {int n_reg_rules; char* alpha2; struct ieee80211_reg_rule* reg_rules; } ;
struct TYPE_4__ {scalar_t__ max_bandwidth_khz; void* start_freq_khz; void* end_freq_khz; } ;
struct TYPE_3__ {int /*<<< orphan*/  max_eirp; } ;
struct ieee80211_reg_rule {TYPE_2__ freq_range; int /*<<< orphan*/  flags; TYPE_1__ power_rule; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;

/* Variables and functions */
 int /*<<< orphan*/  DBM_TO_MBM (int) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct ieee80211_regdomain* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* MHZ_TO_KHZ (int) ; 
 int MWIFIEX_CHANNEL_DFS ; 
 int MWIFIEX_CHANNEL_DISABLED ; 
 int MWIFIEX_CHANNEL_NOHT40 ; 
 int MWIFIEX_CHANNEL_NOHT80 ; 
 int MWIFIEX_CHANNEL_PASSIVE ; 
 int NL80211_BAND_2GHZ ; 
 int NL80211_BAND_5GHZ ; 
 int NL80211_MAX_SUPP_REG_RULES ; 
 int /*<<< orphan*/  NL80211_RRF_DFS ; 
 int /*<<< orphan*/  NL80211_RRF_NO_IR ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int ieee80211_channel_to_frequency (int,int) ; 
 int /*<<< orphan*/  kfree (struct ieee80211_regdomain*) ; 
 struct ieee80211_regdomain* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_rules ; 
 int /*<<< orphan*/  struct_size (struct ieee80211_regdomain*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct ieee80211_regdomain *
mwifiex_create_custom_regdomain(struct mwifiex_private *priv,
				u8 *buf, u16 buf_len)
{
	u16 num_chan = buf_len / 2;
	struct ieee80211_regdomain *regd;
	struct ieee80211_reg_rule *rule;
	bool new_rule;
	int idx, freq, prev_freq = 0;
	u32 bw, prev_bw = 0;
	u8 chflags, prev_chflags = 0, valid_rules = 0;

	if (WARN_ON_ONCE(num_chan > NL80211_MAX_SUPP_REG_RULES))
		return ERR_PTR(-EINVAL);

	regd = kzalloc(struct_size(regd, reg_rules, num_chan), GFP_KERNEL);
	if (!regd)
		return ERR_PTR(-ENOMEM);

	for (idx = 0; idx < num_chan; idx++) {
		u8 chan;
		enum nl80211_band band;

		chan = *buf++;
		if (!chan) {
			kfree(regd);
			return NULL;
		}
		chflags = *buf++;
		band = (chan <= 14) ? NL80211_BAND_2GHZ : NL80211_BAND_5GHZ;
		freq = ieee80211_channel_to_frequency(chan, band);
		new_rule = false;

		if (chflags & MWIFIEX_CHANNEL_DISABLED)
			continue;

		if (band == NL80211_BAND_5GHZ) {
			if (!(chflags & MWIFIEX_CHANNEL_NOHT80))
				bw = MHZ_TO_KHZ(80);
			else if (!(chflags & MWIFIEX_CHANNEL_NOHT40))
				bw = MHZ_TO_KHZ(40);
			else
				bw = MHZ_TO_KHZ(20);
		} else {
			if (!(chflags & MWIFIEX_CHANNEL_NOHT40))
				bw = MHZ_TO_KHZ(40);
			else
				bw = MHZ_TO_KHZ(20);
		}

		if (idx == 0 || prev_chflags != chflags || prev_bw != bw ||
		    freq - prev_freq > 20) {
			valid_rules++;
			new_rule = true;
		}

		rule = &regd->reg_rules[valid_rules - 1];

		rule->freq_range.end_freq_khz = MHZ_TO_KHZ(freq + 10);

		prev_chflags = chflags;
		prev_freq = freq;
		prev_bw = bw;

		if (!new_rule)
			continue;

		rule->freq_range.start_freq_khz = MHZ_TO_KHZ(freq - 10);
		rule->power_rule.max_eirp = DBM_TO_MBM(19);

		if (chflags & MWIFIEX_CHANNEL_PASSIVE)
			rule->flags = NL80211_RRF_NO_IR;

		if (chflags & MWIFIEX_CHANNEL_DFS)
			rule->flags = NL80211_RRF_DFS;

		rule->freq_range.max_bandwidth_khz = bw;
	}

	regd->n_reg_rules = valid_rules;
	regd->alpha2[0] = '9';
	regd->alpha2[1] = '9';

	return regd;
}