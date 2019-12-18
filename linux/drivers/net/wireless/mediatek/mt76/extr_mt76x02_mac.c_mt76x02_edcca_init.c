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
struct TYPE_3__ {struct ieee80211_channel* chan; } ;
struct TYPE_4__ {TYPE_1__ chandef; } ;
struct mt76x02_dev {int ed_monitor_learning; int /*<<< orphan*/  ed_time; TYPE_2__ mt76; scalar_t__ ed_monitor; scalar_t__ ed_silent; scalar_t__ ed_trigger; } ;
struct ieee80211_channel {scalar_t__ band; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGC ; 
 int /*<<< orphan*/  GENMASK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_BBP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT_ED_CCA_TIMER ; 
 int /*<<< orphan*/  MT_TXOP_CTRL_CFG ; 
 int /*<<< orphan*/  MT_TXOP_ED_CCA_EN ; 
 int /*<<< orphan*/  MT_TXOP_HLDR_ET ; 
 int /*<<< orphan*/  MT_TXOP_HLDR_TX40M_BLK_EN ; 
 int /*<<< orphan*/  MT_TX_CFACK_EN ; 
 int /*<<< orphan*/  MT_TX_LINK_CFG ; 
 scalar_t__ NL80211_BAND_5GHZ ; 
 scalar_t__ is_mt76x2 (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  ktime_get_boottime () ; 
 int /*<<< orphan*/  mt76_clear (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_rmw (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_rr (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_set (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76x02_edcca_tx_enable (struct mt76x02_dev*,int) ; 

void mt76x02_edcca_init(struct mt76x02_dev *dev)
{
	dev->ed_trigger = 0;
	dev->ed_silent = 0;

	if (dev->ed_monitor) {
		struct ieee80211_channel *chan = dev->mt76.chandef.chan;
		u8 ed_th = chan->band == NL80211_BAND_5GHZ ? 0x0e : 0x20;

		mt76_clear(dev, MT_TX_LINK_CFG, MT_TX_CFACK_EN);
		mt76_set(dev, MT_TXOP_CTRL_CFG, MT_TXOP_ED_CCA_EN);
		mt76_rmw(dev, MT_BBP(AGC, 2), GENMASK(15, 0),
			 ed_th << 8 | ed_th);
		mt76_set(dev, MT_TXOP_HLDR_ET, MT_TXOP_HLDR_TX40M_BLK_EN);
	} else {
		mt76_set(dev, MT_TX_LINK_CFG, MT_TX_CFACK_EN);
		mt76_clear(dev, MT_TXOP_CTRL_CFG, MT_TXOP_ED_CCA_EN);
		if (is_mt76x2(dev)) {
			mt76_wr(dev, MT_BBP(AGC, 2), 0x00007070);
			mt76_set(dev, MT_TXOP_HLDR_ET,
				 MT_TXOP_HLDR_TX40M_BLK_EN);
		} else {
			mt76_wr(dev, MT_BBP(AGC, 2), 0x003a6464);
			mt76_clear(dev, MT_TXOP_HLDR_ET,
				   MT_TXOP_HLDR_TX40M_BLK_EN);
		}
	}
	mt76x02_edcca_tx_enable(dev, true);
	dev->ed_monitor_learning = true;

	/* clear previous CCA timer value */
	mt76_rr(dev, MT_ED_CCA_TIMER);
	dev->ed_time = ktime_get_boottime();
}