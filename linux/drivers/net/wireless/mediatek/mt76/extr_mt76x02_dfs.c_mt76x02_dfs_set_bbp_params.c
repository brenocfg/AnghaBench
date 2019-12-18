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
typedef  size_t u8 ;
typedef  int u32 ;
struct mt76x02_radar_specs {int avg_len; int mode; int e_high; int e_low; int t_low; int t_high; int b_low; int b_high; int w_high; int w_low; int w_margin; int t_margin; int event_expiration; int pwr_jmp; } ;
struct TYPE_5__ {int width; TYPE_1__* chan; } ;
struct TYPE_6__ {int region; TYPE_2__ chandef; } ;
struct mt76x02_dev {TYPE_3__ mt76; } ;
struct TYPE_4__ {int center_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFS ; 
 int /*<<< orphan*/  IBI ; 
 int /*<<< orphan*/  MT_BBP (int /*<<< orphan*/ ,int) ; 
 int MT_DFS_CH_EN ; 
 int MT_DFS_DELTA_DELAY ; 
 int MT_DFS_NUM_ENGINES ; 
 int MT_DFS_PKT_END_MASK ; 
 int MT_DFS_PWR_DOWN_TIME ; 
 int MT_DFS_PWR_GAIN_OFFSET ; 
 int MT_DFS_RX_PE_MASK ; 
 int MT_DFS_SYM_ROUND ; 
 int MT_DFS_VGA_MASK ; 
#define  NL80211_CHAN_WIDTH_40 133 
#define  NL80211_CHAN_WIDTH_80 132 
#define  NL80211_DFS_ETSI 131 
#define  NL80211_DFS_FCC 130 
#define  NL80211_DFS_JP 129 
#define  NL80211_DFS_UNSET 128 
 struct mt76x02_radar_specs* etsi_radar_specs ; 
 struct mt76x02_radar_specs* fcc_radar_specs ; 
 struct mt76x02_radar_specs* jp_w53_radar_specs ; 
 struct mt76x02_radar_specs* jp_w56_radar_specs ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mt76x02_dfs_set_bbp_params(struct mt76x02_dev *dev)
{
	const struct mt76x02_radar_specs *radar_specs;
	u8 i, shift;
	u32 data;

	switch (dev->mt76.chandef.width) {
	case NL80211_CHAN_WIDTH_40:
		shift = MT_DFS_NUM_ENGINES;
		break;
	case NL80211_CHAN_WIDTH_80:
		shift = 2 * MT_DFS_NUM_ENGINES;
		break;
	default:
		shift = 0;
		break;
	}

	switch (dev->mt76.region) {
	case NL80211_DFS_FCC:
		radar_specs = &fcc_radar_specs[shift];
		break;
	case NL80211_DFS_ETSI:
		radar_specs = &etsi_radar_specs[shift];
		break;
	case NL80211_DFS_JP:
		if (dev->mt76.chandef.chan->center_freq >= 5250 &&
		    dev->mt76.chandef.chan->center_freq <= 5350)
			radar_specs = &jp_w53_radar_specs[shift];
		else
			radar_specs = &jp_w56_radar_specs[shift];
		break;
	case NL80211_DFS_UNSET:
	default:
		return;
	}

	data = (MT_DFS_VGA_MASK << 16) |
	       (MT_DFS_PWR_GAIN_OFFSET << 12) |
	       (MT_DFS_PWR_DOWN_TIME << 8) |
	       (MT_DFS_SYM_ROUND << 4) |
	       (MT_DFS_DELTA_DELAY & 0xf);
	mt76_wr(dev, MT_BBP(DFS, 2), data);

	data = (MT_DFS_RX_PE_MASK << 16) | MT_DFS_PKT_END_MASK;
	mt76_wr(dev, MT_BBP(DFS, 3), data);

	for (i = 0; i < MT_DFS_NUM_ENGINES; i++) {
		/* configure engine */
		mt76_wr(dev, MT_BBP(DFS, 0), i);

		/* detection mode + avg_len */
		data = ((radar_specs[i].avg_len & 0x1ff) << 16) |
		       (radar_specs[i].mode & 0xf);
		mt76_wr(dev, MT_BBP(DFS, 4), data);

		/* dfs energy */
		data = ((radar_specs[i].e_high & 0x0fff) << 16) |
		       (radar_specs[i].e_low & 0x0fff);
		mt76_wr(dev, MT_BBP(DFS, 5), data);

		/* dfs period */
		mt76_wr(dev, MT_BBP(DFS, 7), radar_specs[i].t_low);
		mt76_wr(dev, MT_BBP(DFS, 9), radar_specs[i].t_high);

		/* dfs burst */
		mt76_wr(dev, MT_BBP(DFS, 11), radar_specs[i].b_low);
		mt76_wr(dev, MT_BBP(DFS, 13), radar_specs[i].b_high);

		/* dfs width */
		data = ((radar_specs[i].w_high & 0x0fff) << 16) |
		       (radar_specs[i].w_low & 0x0fff);
		mt76_wr(dev, MT_BBP(DFS, 14), data);

		/* dfs margins */
		data = (radar_specs[i].w_margin << 16) |
		       radar_specs[i].t_margin;
		mt76_wr(dev, MT_BBP(DFS, 15), data);

		/* dfs event expiration */
		mt76_wr(dev, MT_BBP(DFS, 17), radar_specs[i].event_expiration);

		/* dfs pwr adj */
		mt76_wr(dev, MT_BBP(DFS, 30), radar_specs[i].pwr_jmp);
	}

	/* reset status */
	mt76_wr(dev, MT_BBP(DFS, 1), 0xf);
	mt76_wr(dev, MT_BBP(DFS, 36), 0x3);

	/* enable detection*/
	mt76_wr(dev, MT_BBP(DFS, 0), MT_DFS_CH_EN << 16);
	mt76_wr(dev, MT_BBP(IBI, 11), 0x0c350001);
}