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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int idx; } ;
struct mt7603_sta {int ps; TYPE_1__ wcid; } ;
struct mt7603_dev {int /*<<< orphan*/  ps_lock; } ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT_PSE_RTA ; 
 int MT_PSE_RTA_BUSY ; 
 int /*<<< orphan*/  MT_PSE_RTA_PORT_ID ; 
 int /*<<< orphan*/  MT_PSE_RTA_QUEUE_ID ; 
 int /*<<< orphan*/  MT_PSE_RTA_REDIRECT_EN ; 
 int /*<<< orphan*/  MT_PSE_RTA_TAG_ID ; 
 int MT_PSE_RTA_WRITE ; 
 int /*<<< orphan*/  MT_WTBL1_OR ; 
 int /*<<< orphan*/  MT_WTBL1_OR_PSM_WRITE ; 
 int MT_WTBL1_W3_POWER_SAVE ; 
 int /*<<< orphan*/  mt7603_filter_tx (struct mt7603_dev*,int,int) ; 
 scalar_t__ mt7603_wtbl1_addr (int) ; 
 int /*<<< orphan*/  mt76_clear (struct mt7603_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_poll (struct mt7603_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_rmw (struct mt7603_dev*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  mt76_set (struct mt7603_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wr (struct mt7603_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void mt7603_wtbl_set_ps(struct mt7603_dev *dev, struct mt7603_sta *sta,
			bool enabled)
{
	int idx = sta->wcid.idx;
	u32 addr;

	spin_lock_bh(&dev->ps_lock);

	if (sta->ps == enabled)
		goto out;

	mt76_wr(dev, MT_PSE_RTA,
		FIELD_PREP(MT_PSE_RTA_TAG_ID, idx) |
		FIELD_PREP(MT_PSE_RTA_PORT_ID, 0) |
		FIELD_PREP(MT_PSE_RTA_QUEUE_ID, 1) |
		FIELD_PREP(MT_PSE_RTA_REDIRECT_EN, enabled) |
		MT_PSE_RTA_WRITE | MT_PSE_RTA_BUSY);

	mt76_poll(dev, MT_PSE_RTA, MT_PSE_RTA_BUSY, 0, 5000);

	if (enabled)
		mt7603_filter_tx(dev, idx, false);

	addr = mt7603_wtbl1_addr(idx);
	mt76_set(dev, MT_WTBL1_OR, MT_WTBL1_OR_PSM_WRITE);
	mt76_rmw(dev, addr + 3 * 4, MT_WTBL1_W3_POWER_SAVE,
		 enabled * MT_WTBL1_W3_POWER_SAVE);
	mt76_clear(dev, MT_WTBL1_OR, MT_WTBL1_OR_PSM_WRITE);
	sta->ps = enabled;

out:
	spin_unlock_bh(&dev->ps_lock);
}