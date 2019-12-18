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
typedef  int u32 ;
struct mt76x02_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_WCID_DROP (int /*<<< orphan*/ ) ; 
 int MT_WCID_DROP_MASK (int /*<<< orphan*/ ) ; 
 int mt76_rr (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 

void mt76x02_mac_wcid_set_drop(struct mt76x02_dev *dev, u8 idx, bool drop)
{
	u32 val = mt76_rr(dev, MT_WCID_DROP(idx));
	u32 bit = MT_WCID_DROP_MASK(idx);

	/* prevent unnecessary writes */
	if ((val & bit) != (bit * drop))
		mt76_wr(dev, MT_WCID_DROP(idx), (val & ~bit) | (bit * drop));
}