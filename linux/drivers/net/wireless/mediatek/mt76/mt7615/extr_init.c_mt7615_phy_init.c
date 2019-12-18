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
 int /*<<< orphan*/  MT_WF_PHY_WF2_RFCTRL0 ; 
 int /*<<< orphan*/  MT_WF_PHY_WF2_RFCTRL0_LPBCN_EN ; 
 int /*<<< orphan*/  mt76_rmw (struct mt7615_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mt7615_phy_init(struct mt7615_dev *dev)
{
	/* disable band 0 rf low power beacon mode */
	mt76_rmw(dev, MT_WF_PHY_WF2_RFCTRL0, MT_WF_PHY_WF2_RFCTRL0_LPBCN_EN,
		 MT_WF_PHY_WF2_RFCTRL0_LPBCN_EN);
}