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
typedef  int u32 ;
struct mt76x02_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGC ; 
 int /*<<< orphan*/  DFS ; 
 int FIELD_GET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT_BBP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT_BBP_AGC_LNA_HIGH_GAIN ; 
 int MT_DFS_CH_EN ; 
 scalar_t__ is_mt76x2 (struct mt76x02_dev*) ; 
 int mt76_rr (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 

void mt76x02_phy_dfs_adjust_agc(struct mt76x02_dev *dev)
{
	u32 agc_r8, agc_r4, val_r8, val_r4, dfs_r31;

	agc_r8 = mt76_rr(dev, MT_BBP(AGC, 8));
	agc_r4 = mt76_rr(dev, MT_BBP(AGC, 4));

	val_r8 = (agc_r8 & 0x00007e00) >> 9;
	val_r4 = agc_r4 & ~0x1f000000;
	val_r4 += (((val_r8 + 1) >> 1) << 24);
	mt76_wr(dev, MT_BBP(AGC, 4), val_r4);

	dfs_r31 = FIELD_GET(MT_BBP_AGC_LNA_HIGH_GAIN, val_r4);
	dfs_r31 += val_r8;
	dfs_r31 -= (agc_r8 & 0x00000038) >> 3;
	dfs_r31 = (dfs_r31 << 16) | 0x00000307;
	mt76_wr(dev, MT_BBP(DFS, 31), dfs_r31);

	if (is_mt76x2(dev)) {
		mt76_wr(dev, MT_BBP(DFS, 32), 0x00040071);
	} else {
		/* disable hw detector */
		mt76_wr(dev, MT_BBP(DFS, 0), 0);
		/* enable hw detector */
		mt76_wr(dev, MT_BBP(DFS, 0), MT_DFS_CH_EN << 16);
	}
}