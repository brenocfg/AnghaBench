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
struct mt7615_dev {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  GENMASK (int,int) ; 
 int /*<<< orphan*/  MT_WF_PHY_R0_B0_PHYMUX_5 ; 
 int /*<<< orphan*/  mt76_clear (struct mt7615_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_set (struct mt7615_dev*,int /*<<< orphan*/ ,int) ; 

void mt7615_mac_cca_stats_reset(struct mt7615_dev *dev)
{
	mt76_clear(dev, MT_WF_PHY_R0_B0_PHYMUX_5, GENMASK(22, 20));
	mt76_set(dev, MT_WF_PHY_R0_B0_PHYMUX_5, BIT(22) | BIT(20));
}