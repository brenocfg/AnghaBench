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
struct mt7615_dev {int ofdm_sensitivity; int cck_sensitivity; int /*<<< orphan*/  last_cca_adj; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_WF_PHY_B0_MIN_PRI_PWR ; 
 int /*<<< orphan*/  MT_WF_PHY_B0_PD_CCK (int) ; 
 int /*<<< orphan*/  MT_WF_PHY_B0_PD_CCK_MASK ; 
 int /*<<< orphan*/  MT_WF_PHY_B0_PD_OFDM (int) ; 
 int /*<<< orphan*/  MT_WF_PHY_B0_PD_OFDM_MASK ; 
 int /*<<< orphan*/  MT_WF_PHY_B0_RXTD_CCK_PD ; 
 int /*<<< orphan*/  MT_WF_PHY_B1_MIN_PRI_PWR ; 
 int /*<<< orphan*/  MT_WF_PHY_B1_PD_CCK (int) ; 
 int /*<<< orphan*/  MT_WF_PHY_B1_PD_CCK_MASK ; 
 int /*<<< orphan*/  MT_WF_PHY_B1_PD_OFDM (int) ; 
 int /*<<< orphan*/  MT_WF_PHY_B1_PD_OFDM_MASK ; 
 int /*<<< orphan*/  MT_WF_PHY_B1_RXTD_CCK_PD ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mt76_rmw (struct mt7615_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mt7615_mac_set_default_sensitivity(struct mt7615_dev *dev)
{
	mt76_rmw(dev, MT_WF_PHY_B0_MIN_PRI_PWR,
		 MT_WF_PHY_B0_PD_OFDM_MASK,
		 MT_WF_PHY_B0_PD_OFDM(0x13c));
	mt76_rmw(dev, MT_WF_PHY_B1_MIN_PRI_PWR,
		 MT_WF_PHY_B1_PD_OFDM_MASK,
		 MT_WF_PHY_B1_PD_OFDM(0x13c));

	mt76_rmw(dev, MT_WF_PHY_B0_RXTD_CCK_PD,
		 MT_WF_PHY_B0_PD_CCK_MASK,
		 MT_WF_PHY_B0_PD_CCK(0x92));
	mt76_rmw(dev, MT_WF_PHY_B1_RXTD_CCK_PD,
		 MT_WF_PHY_B1_PD_CCK_MASK,
		 MT_WF_PHY_B1_PD_CCK(0x92));

	dev->ofdm_sensitivity = -98;
	dev->cck_sensitivity = -110;
	dev->last_cca_adj = jiffies;
}