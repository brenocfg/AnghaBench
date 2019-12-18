#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct cfg80211_chan_def {int center_freq1; int width; TYPE_1__* chan; } ;
struct brcmu_d11inf {int /*<<< orphan*/  (* encchspec ) (struct brcmu_chan*) ;} ;
struct brcmu_chan {int /*<<< orphan*/  chspec; int /*<<< orphan*/  band; int /*<<< orphan*/  sb; int /*<<< orphan*/  bw; int /*<<< orphan*/  chnum; } ;
typedef  int s32 ;
struct TYPE_2__ {int center_freq; int band; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMU_CHAN_BAND_2G ; 
 int /*<<< orphan*/  BRCMU_CHAN_BAND_5G ; 
 int /*<<< orphan*/  BRCMU_CHAN_BW_160 ; 
 int /*<<< orphan*/  BRCMU_CHAN_BW_20 ; 
 int /*<<< orphan*/  BRCMU_CHAN_BW_40 ; 
 int /*<<< orphan*/  BRCMU_CHAN_BW_80 ; 
 int /*<<< orphan*/  BRCMU_CHAN_SB_L ; 
 int /*<<< orphan*/  BRCMU_CHAN_SB_LL ; 
 int /*<<< orphan*/  BRCMU_CHAN_SB_LLL ; 
 int /*<<< orphan*/  BRCMU_CHAN_SB_LLU ; 
 int /*<<< orphan*/  BRCMU_CHAN_SB_LU ; 
 int /*<<< orphan*/  BRCMU_CHAN_SB_LUL ; 
 int /*<<< orphan*/  BRCMU_CHAN_SB_LUU ; 
 int /*<<< orphan*/  BRCMU_CHAN_SB_U ; 
 int /*<<< orphan*/  BRCMU_CHAN_SB_UL ; 
 int /*<<< orphan*/  BRCMU_CHAN_SB_ULL ; 
 int /*<<< orphan*/  BRCMU_CHAN_SB_ULU ; 
 int /*<<< orphan*/  BRCMU_CHAN_SB_UU ; 
 int /*<<< orphan*/  BRCMU_CHAN_SB_UUL ; 
 int /*<<< orphan*/  BRCMU_CHAN_SB_UUU ; 
#define  NL80211_BAND_2GHZ 138 
#define  NL80211_BAND_5GHZ 137 
#define  NL80211_BAND_60GHZ 136 
#define  NL80211_CHAN_WIDTH_10 135 
#define  NL80211_CHAN_WIDTH_160 134 
#define  NL80211_CHAN_WIDTH_20 133 
#define  NL80211_CHAN_WIDTH_20_NOHT 132 
#define  NL80211_CHAN_WIDTH_40 131 
#define  NL80211_CHAN_WIDTH_5 130 
#define  NL80211_CHAN_WIDTH_80 129 
#define  NL80211_CHAN_WIDTH_80P80 128 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  ieee80211_frequency_to_channel (int) ; 
 int /*<<< orphan*/  stub1 (struct brcmu_chan*) ; 

__attribute__((used)) static u16 chandef_to_chanspec(struct brcmu_d11inf *d11inf,
			       struct cfg80211_chan_def *ch)
{
	struct brcmu_chan ch_inf;
	s32 primary_offset;

	brcmf_dbg(TRACE, "chandef: control %d center %d width %d\n",
		  ch->chan->center_freq, ch->center_freq1, ch->width);
	ch_inf.chnum = ieee80211_frequency_to_channel(ch->center_freq1);
	primary_offset = ch->chan->center_freq - ch->center_freq1;
	switch (ch->width) {
	case NL80211_CHAN_WIDTH_20:
	case NL80211_CHAN_WIDTH_20_NOHT:
		ch_inf.bw = BRCMU_CHAN_BW_20;
		WARN_ON(primary_offset != 0);
		break;
	case NL80211_CHAN_WIDTH_40:
		ch_inf.bw = BRCMU_CHAN_BW_40;
		if (primary_offset > 0)
			ch_inf.sb = BRCMU_CHAN_SB_U;
		else
			ch_inf.sb = BRCMU_CHAN_SB_L;
		break;
	case NL80211_CHAN_WIDTH_80:
		ch_inf.bw = BRCMU_CHAN_BW_80;
		if (primary_offset == -30)
			ch_inf.sb = BRCMU_CHAN_SB_LL;
		else if (primary_offset == -10)
			ch_inf.sb = BRCMU_CHAN_SB_LU;
		else if (primary_offset == 10)
			ch_inf.sb = BRCMU_CHAN_SB_UL;
		else
			ch_inf.sb = BRCMU_CHAN_SB_UU;
		break;
	case NL80211_CHAN_WIDTH_160:
		ch_inf.bw = BRCMU_CHAN_BW_160;
		if (primary_offset == -70)
			ch_inf.sb = BRCMU_CHAN_SB_LLL;
		else if (primary_offset == -50)
			ch_inf.sb = BRCMU_CHAN_SB_LLU;
		else if (primary_offset == -30)
			ch_inf.sb = BRCMU_CHAN_SB_LUL;
		else if (primary_offset == -10)
			ch_inf.sb = BRCMU_CHAN_SB_LUU;
		else if (primary_offset == 10)
			ch_inf.sb = BRCMU_CHAN_SB_ULL;
		else if (primary_offset == 30)
			ch_inf.sb = BRCMU_CHAN_SB_ULU;
		else if (primary_offset == 50)
			ch_inf.sb = BRCMU_CHAN_SB_UUL;
		else
			ch_inf.sb = BRCMU_CHAN_SB_UUU;
		break;
	case NL80211_CHAN_WIDTH_80P80:
	case NL80211_CHAN_WIDTH_5:
	case NL80211_CHAN_WIDTH_10:
	default:
		WARN_ON_ONCE(1);
	}
	switch (ch->chan->band) {
	case NL80211_BAND_2GHZ:
		ch_inf.band = BRCMU_CHAN_BAND_2G;
		break;
	case NL80211_BAND_5GHZ:
		ch_inf.band = BRCMU_CHAN_BAND_5G;
		break;
	case NL80211_BAND_60GHZ:
	default:
		WARN_ON_ONCE(1);
	}
	d11inf->encchspec(&ch_inf);

	brcmf_dbg(TRACE, "chanspec: 0x%x\n", ch_inf.chspec);
	return ch_inf.chspec;
}