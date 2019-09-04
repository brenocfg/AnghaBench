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
typedef  scalar_t__ u32 ;
struct phy_device {int advertising; } ;
struct TYPE_3__ {struct phy_device* phydev; } ;
struct TYPE_4__ {TYPE_1__ mac; } ;
struct hclge_dev {TYPE_2__ hw; } ;

/* Variables and functions */
 int ADVERTISED_Asym_Pause ; 
 int ADVERTISED_Pause ; 

__attribute__((used)) static void hclge_set_flowctrl_adv(struct hclge_dev *hdev, u32 rx_en, u32 tx_en)
{
	struct phy_device *phydev = hdev->hw.mac.phydev;

	if (!phydev)
		return;

	phydev->advertising &= ~(ADVERTISED_Pause | ADVERTISED_Asym_Pause);

	if (rx_en)
		phydev->advertising |= ADVERTISED_Pause | ADVERTISED_Asym_Pause;

	if (tx_en)
		phydev->advertising ^= ADVERTISED_Asym_Pause;
}