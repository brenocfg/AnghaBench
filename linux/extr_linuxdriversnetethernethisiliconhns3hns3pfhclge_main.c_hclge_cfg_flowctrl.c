#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct phy_device {int advertising; scalar_t__ duplex; scalar_t__ asym_pause; scalar_t__ pause; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  link; } ;
struct TYPE_3__ {struct phy_device* phydev; } ;
struct TYPE_4__ {TYPE_1__ mac; } ;
struct hclge_dev {TYPE_2__ hw; } ;

/* Variables and functions */
 int ADVERTISED_Asym_Pause ; 
 int ADVERTISED_Pause ; 
 int /*<<< orphan*/  ADVERTISE_PAUSE_ASYM ; 
 int /*<<< orphan*/  ADVERTISE_PAUSE_CAP ; 
 int FLOW_CTRL_RX ; 
 int FLOW_CTRL_TX ; 
 scalar_t__ HCLGE_MAC_HALF ; 
 int /*<<< orphan*/  LPA_PAUSE_ASYM ; 
 int /*<<< orphan*/  LPA_PAUSE_CAP ; 
 int hclge_cfg_pauseparam (struct hclge_dev*,int,int) ; 
 int mii_resolve_flowctrl_fdx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int hclge_cfg_flowctrl(struct hclge_dev *hdev)
{
	struct phy_device *phydev = hdev->hw.mac.phydev;
	u16 remote_advertising = 0;
	u16 local_advertising = 0;
	u32 rx_pause, tx_pause;
	u8 flowctl;

	if (!phydev->link || !phydev->autoneg)
		return 0;

	if (phydev->advertising & ADVERTISED_Pause)
		local_advertising = ADVERTISE_PAUSE_CAP;

	if (phydev->advertising & ADVERTISED_Asym_Pause)
		local_advertising |= ADVERTISE_PAUSE_ASYM;

	if (phydev->pause)
		remote_advertising = LPA_PAUSE_CAP;

	if (phydev->asym_pause)
		remote_advertising |= LPA_PAUSE_ASYM;

	flowctl = mii_resolve_flowctrl_fdx(local_advertising,
					   remote_advertising);
	tx_pause = flowctl & FLOW_CTRL_TX;
	rx_pause = flowctl & FLOW_CTRL_RX;

	if (phydev->duplex == HCLGE_MAC_HALF) {
		tx_pause = 0;
		rx_pause = 0;
	}

	return hclge_cfg_pauseparam(hdev, rx_pause, tx_pause);
}