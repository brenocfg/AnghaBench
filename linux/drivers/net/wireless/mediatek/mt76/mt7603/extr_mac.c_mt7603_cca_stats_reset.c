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
 int /*<<< orphan*/  MT_PHYCTRL (int) ; 
 int /*<<< orphan*/  MT_PHYCTRL_2_STATUS_EN ; 
 int /*<<< orphan*/  MT_PHYCTRL_2_STATUS_RESET ; 
 int /*<<< orphan*/  mt76_clear (struct mt7603_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_set (struct mt7603_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mt7603_cca_stats_reset(struct mt7603_dev *dev)
{
	mt76_set(dev, MT_PHYCTRL(2), MT_PHYCTRL_2_STATUS_RESET);
	mt76_clear(dev, MT_PHYCTRL(2), MT_PHYCTRL_2_STATUS_RESET);
	mt76_set(dev, MT_PHYCTRL(2), MT_PHYCTRL_2_STATUS_EN);
}