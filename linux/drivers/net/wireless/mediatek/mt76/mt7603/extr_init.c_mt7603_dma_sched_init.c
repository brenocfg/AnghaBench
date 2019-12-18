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
struct mt7603_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 scalar_t__ MT7603_REV_E2 ; 
 int /*<<< orphan*/  MT_BMAP_0 ; 
 int /*<<< orphan*/  MT_BMAP_1 ; 
 int /*<<< orphan*/  MT_GROUP_THRESH (int) ; 
 int /*<<< orphan*/  MT_HIGH_PRIORITY_1 ; 
 int /*<<< orphan*/  MT_HIGH_PRIORITY_2 ; 
 int /*<<< orphan*/  MT_PAGE_COUNT (int) ; 
 int /*<<< orphan*/  MT_PRIORITY_MASK ; 
 int /*<<< orphan*/  MT_PSE_FC_P0 ; 
 int /*<<< orphan*/  MT_PSE_FC_P0_MAX_QUOTA ; 
 int /*<<< orphan*/  MT_PSE_FRP ; 
 int /*<<< orphan*/  MT_PSE_FRP_P0 ; 
 int /*<<< orphan*/  MT_PSE_FRP_P1 ; 
 int /*<<< orphan*/  MT_PSE_FRP_P2_RQ2 ; 
 int /*<<< orphan*/  MT_QUEUE_PRIORITY_1 ; 
 int /*<<< orphan*/  MT_QUEUE_PRIORITY_2 ; 
 int /*<<< orphan*/  MT_RSV_MAX_THRESH ; 
 int /*<<< orphan*/  MT_SCH_1 ; 
 int /*<<< orphan*/  MT_SCH_2 ; 
 int /*<<< orphan*/  MT_SCH_4 ; 
 int /*<<< orphan*/  MT_TXTIME_THRESH (int) ; 
 scalar_t__ is_mt7603 (struct mt7603_dev*) ; 
 int mt76_get_field (struct mt7603_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_set (struct mt7603_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wr (struct mt7603_dev*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mt76xx_rev (struct mt7603_dev*) ; 

__attribute__((used)) static void
mt7603_dma_sched_init(struct mt7603_dev *dev)
{
	int page_size = 128;
	int page_count;
	int max_len = 1792;
	int max_amsdu_pages = 4096 / page_size;
	int max_mcu_len = 4096;
	int max_beacon_len = 512 * 4 + max_len;
	int max_mcast_pages = 4 * max_len / page_size;
	int reserved_count = 0;
	int beacon_pages;
	int mcu_pages;
	int i;

	page_count = mt76_get_field(dev, MT_PSE_FC_P0,
				    MT_PSE_FC_P0_MAX_QUOTA);
	beacon_pages = 4 * (max_beacon_len / page_size);
	mcu_pages = max_mcu_len / page_size;

	mt76_wr(dev, MT_PSE_FRP,
		FIELD_PREP(MT_PSE_FRP_P0, 7) |
		FIELD_PREP(MT_PSE_FRP_P1, 6) |
		FIELD_PREP(MT_PSE_FRP_P2_RQ2, 4));

	mt76_wr(dev, MT_HIGH_PRIORITY_1, 0x55555553);
	mt76_wr(dev, MT_HIGH_PRIORITY_2, 0x78555555);

	mt76_wr(dev, MT_QUEUE_PRIORITY_1, 0x2b1a096e);
	mt76_wr(dev, MT_QUEUE_PRIORITY_2, 0x785f4d3c);

	mt76_wr(dev, MT_PRIORITY_MASK, 0xffffffff);

	mt76_wr(dev, MT_SCH_1, page_count | (2 << 28));
	mt76_wr(dev, MT_SCH_2, max_amsdu_pages);

	for (i = 0; i <= 4; i++)
		mt76_wr(dev, MT_PAGE_COUNT(i), max_amsdu_pages);
	reserved_count += 5 * max_amsdu_pages;

	mt76_wr(dev, MT_PAGE_COUNT(5), mcu_pages);
	reserved_count += mcu_pages;

	mt76_wr(dev, MT_PAGE_COUNT(7), beacon_pages);
	reserved_count += beacon_pages;

	mt76_wr(dev, MT_PAGE_COUNT(8), max_mcast_pages);
	reserved_count += max_mcast_pages;

	if (is_mt7603(dev))
		reserved_count = 0;

	mt76_wr(dev, MT_RSV_MAX_THRESH, page_count - reserved_count);

	if (is_mt7603(dev) && mt76xx_rev(dev) >= MT7603_REV_E2) {
		mt76_wr(dev, MT_GROUP_THRESH(0),
			page_count - beacon_pages - mcu_pages);
		mt76_wr(dev, MT_GROUP_THRESH(1), beacon_pages);
		mt76_wr(dev, MT_BMAP_0, 0x0080ff5f);
		mt76_wr(dev, MT_GROUP_THRESH(2), mcu_pages);
		mt76_wr(dev, MT_BMAP_1, 0x00000020);
	} else {
		mt76_wr(dev, MT_GROUP_THRESH(0), page_count);
		mt76_wr(dev, MT_BMAP_0, 0xffff);
	}

	mt76_wr(dev, MT_SCH_4, 0);

	for (i = 0; i <= 15; i++)
		mt76_wr(dev, MT_TXTIME_THRESH(i), 0xfffff);

	mt76_set(dev, MT_SCH_4, BIT(6));
}