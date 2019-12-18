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
typedef  int /*<<< orphan*/  u8 ;
struct mt7603_dev {int dummy; } ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_BA_CONTROL_0 ; 
 int /*<<< orphan*/  MT_BA_CONTROL_1 ; 
 int MT_BA_CONTROL_1_RESET ; 
 int /*<<< orphan*/  MT_BA_CONTROL_1_TID ; 
 int get_unaligned_le16 (void*) ; 
 int get_unaligned_le32 (void*) ; 
 int /*<<< orphan*/  mt76_wr (struct mt7603_dev*,int /*<<< orphan*/ ,int) ; 

void mt7603_mac_rx_ba_reset(struct mt7603_dev *dev, void *addr, u8 tid)
{
	mt76_wr(dev, MT_BA_CONTROL_0, get_unaligned_le32(addr));
	mt76_wr(dev, MT_BA_CONTROL_1,
		(get_unaligned_le16(addr + 4) |
		 FIELD_PREP(MT_BA_CONTROL_1_TID, tid) |
		 MT_BA_CONTROL_1_RESET));
}