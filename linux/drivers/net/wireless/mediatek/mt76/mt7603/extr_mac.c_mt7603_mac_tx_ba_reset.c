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
struct mt7603_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int FIELD_PREP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MT_AGG_SIZE_LIMIT (int) ; 
 int /*<<< orphan*/  MT_WTBL2_W15_BA_EN_TIDS ; 
 int MT_WTBL2_W15_BA_WIN_SIZE ; 
 int MT_WTBL2_W15_BA_WIN_SIZE_SHIFT ; 
 int mt7603_wtbl2_addr (int) ; 
 int /*<<< orphan*/  mt76_clear (struct mt7603_dev*,int,int) ; 
 int /*<<< orphan*/  mt76_rmw (struct mt7603_dev*,int,int,int) ; 

void mt7603_mac_tx_ba_reset(struct mt7603_dev *dev, int wcid, int tid,
			    int ba_size)
{
	u32 addr = mt7603_wtbl2_addr(wcid);
	u32 tid_mask = FIELD_PREP(MT_WTBL2_W15_BA_EN_TIDS, BIT(tid)) |
		       (MT_WTBL2_W15_BA_WIN_SIZE <<
			(tid * MT_WTBL2_W15_BA_WIN_SIZE_SHIFT));
	u32 tid_val;
	int i;

	if (ba_size < 0) {
		/* disable */
		mt76_clear(dev, addr + (15 * 4), tid_mask);
		return;
	}

	for (i = 7; i > 0; i--) {
		if (ba_size >= MT_AGG_SIZE_LIMIT(i))
			break;
	}

	tid_val = FIELD_PREP(MT_WTBL2_W15_BA_EN_TIDS, BIT(tid)) |
		  i << (tid * MT_WTBL2_W15_BA_WIN_SIZE_SHIFT);

	mt76_rmw(dev, addr + (15 * 4), tid_mask, tid_val);
}