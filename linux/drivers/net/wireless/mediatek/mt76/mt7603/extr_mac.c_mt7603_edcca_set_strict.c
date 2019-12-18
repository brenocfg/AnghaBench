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
struct mt7603_dev {int ed_strict_mode; scalar_t__ ed_monitor; } ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT_RXTD (int) ; 
 int /*<<< orphan*/  MT_RXTD_13_ACI_TH_EN ; 
 int /*<<< orphan*/  MT_RXTD_6_ACI_TH ; 
 int /*<<< orphan*/  MT_RXTD_6_CCAED_TH ; 
 int /*<<< orphan*/  mt76_rmw_field (struct mt7603_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_wr (struct mt7603_dev*,int /*<<< orphan*/ ,int) ; 

void
mt7603_edcca_set_strict(struct mt7603_dev *dev, bool val)
{
	u32 rxtd_6 = 0xd7c80000;

	if (val == dev->ed_strict_mode)
		return;

	dev->ed_strict_mode = val;

	/* Ensure that ED/CCA does not trigger if disabled */
	if (!dev->ed_monitor)
		rxtd_6 |= FIELD_PREP(MT_RXTD_6_CCAED_TH, 0x34);
	else
		rxtd_6 |= FIELD_PREP(MT_RXTD_6_CCAED_TH, 0x7d);

	if (dev->ed_monitor && !dev->ed_strict_mode)
		rxtd_6 |= FIELD_PREP(MT_RXTD_6_ACI_TH, 0x0f);
	else
		rxtd_6 |= FIELD_PREP(MT_RXTD_6_ACI_TH, 0x10);

	mt76_wr(dev, MT_RXTD(6), rxtd_6);

	mt76_rmw_field(dev, MT_RXTD(13), MT_RXTD_13_ACI_TH_EN,
		       dev->ed_monitor && !dev->ed_strict_mode);
}