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
typedef  int u32 ;
struct TYPE_4__ {int idx; } ;
struct mt7603_sta {TYPE_1__ wcid; } ;
struct mt7603_dev {int dummy; } ;
struct TYPE_6__ {int cap; int /*<<< orphan*/  ampdu_density; int /*<<< orphan*/  ampdu_factor; } ;
struct TYPE_5__ {scalar_t__ cap; } ;
struct ieee80211_sta {TYPE_3__ ht_cap; TYPE_2__ vht_cap; scalar_t__ drv_priv; } ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IEEE80211_HT_CAP_SGI_20 ; 
 int IEEE80211_HT_CAP_SGI_40 ; 
 int MT_WTBL1_W2_ADMISSION_CONTROL ; 
 int /*<<< orphan*/  MT_WTBL1_W2_AMPDU_FACTOR ; 
 int MT_WTBL1_W2_HT ; 
 int MT_WTBL1_W2_KEY_TYPE ; 
 int /*<<< orphan*/  MT_WTBL1_W2_MPDU_DENSITY ; 
 int MT_WTBL1_W2_TXS_BAF_REPORT ; 
 int MT_WTBL1_W2_VHT ; 
 int MT_WTBL2_W9_SHORT_GI_20 ; 
 int MT_WTBL2_W9_SHORT_GI_40 ; 
 int MT_WTBL2_W9_SHORT_GI_80 ; 
 int mt7603_wtbl1_addr (int) ; 
 int mt7603_wtbl2_addr (int) ; 
 int mt76_rr (struct mt7603_dev*,int) ; 
 int /*<<< orphan*/  mt76_wr (struct mt7603_dev*,int,int) ; 

void mt7603_wtbl_update_cap(struct mt7603_dev *dev, struct ieee80211_sta *sta)
{
	struct mt7603_sta *msta = (struct mt7603_sta *)sta->drv_priv;
	int idx = msta->wcid.idx;
	u32 addr;
	u32 val;

	addr = mt7603_wtbl1_addr(idx);

	val = mt76_rr(dev, addr + 2 * 4);
	val &= MT_WTBL1_W2_KEY_TYPE | MT_WTBL1_W2_ADMISSION_CONTROL;
	val |= FIELD_PREP(MT_WTBL1_W2_AMPDU_FACTOR, sta->ht_cap.ampdu_factor) |
	       FIELD_PREP(MT_WTBL1_W2_MPDU_DENSITY, sta->ht_cap.ampdu_density) |
	       MT_WTBL1_W2_TXS_BAF_REPORT;

	if (sta->ht_cap.cap)
		val |= MT_WTBL1_W2_HT;
	if (sta->vht_cap.cap)
		val |= MT_WTBL1_W2_VHT;

	mt76_wr(dev, addr + 2 * 4, val);

	addr = mt7603_wtbl2_addr(idx);
	val = mt76_rr(dev, addr + 9 * 4);
	val &= ~(MT_WTBL2_W9_SHORT_GI_20 | MT_WTBL2_W9_SHORT_GI_40 |
		 MT_WTBL2_W9_SHORT_GI_80);
	if (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_20)
		val |= MT_WTBL2_W9_SHORT_GI_20;
	if (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_40)
		val |= MT_WTBL2_W9_SHORT_GI_40;
	mt76_wr(dev, addr + 9 * 4, val);
}