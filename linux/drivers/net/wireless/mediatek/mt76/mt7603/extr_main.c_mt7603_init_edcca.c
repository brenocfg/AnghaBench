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
struct mt7603_dev {int ed_strict_mode; int /*<<< orphan*/  ed_time; scalar_t__ ed_strong_signal; scalar_t__ ed_monitor; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_MIB_CTL ; 
 int /*<<< orphan*/  MT_MIB_CTL_ED_TIME ; 
 int /*<<< orphan*/  MT_MIB_STAT_ED ; 
 int /*<<< orphan*/  MT_RXTD (int) ; 
 int /*<<< orphan*/  MT_RXTD_8_LOWER_SIGNAL ; 
 int /*<<< orphan*/  ktime_get_boottime () ; 
 int /*<<< orphan*/  mt7603_edcca_set_strict (struct mt7603_dev*,int) ; 
 int /*<<< orphan*/  mt76_clear (struct mt7603_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_rmw_field (struct mt7603_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_rr (struct mt7603_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_set (struct mt7603_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mt7603_init_edcca(struct mt7603_dev *dev)
{
	/* Set lower signal level to -65dBm */
	mt76_rmw_field(dev, MT_RXTD(8), MT_RXTD_8_LOWER_SIGNAL, 0x23);

	/* clear previous energy detect monitor results */
	mt76_rr(dev, MT_MIB_STAT_ED);

	if (dev->ed_monitor)
		mt76_set(dev, MT_MIB_CTL, MT_MIB_CTL_ED_TIME);
	else
		mt76_clear(dev, MT_MIB_CTL, MT_MIB_CTL_ED_TIME);

	dev->ed_strict_mode = 0xff;
	dev->ed_strong_signal = 0;
	dev->ed_time = ktime_get_boottime();

	mt7603_edcca_set_strict(dev, false);
}