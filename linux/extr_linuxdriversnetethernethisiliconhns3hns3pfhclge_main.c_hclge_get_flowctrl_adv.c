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
typedef  int u32 ;
struct phy_device {int advertising; } ;
struct hnae3_handle {int dummy; } ;
struct hclge_vport {struct hclge_dev* back; } ;
struct TYPE_3__ {struct phy_device* phydev; } ;
struct TYPE_4__ {TYPE_1__ mac; } ;
struct hclge_dev {TYPE_2__ hw; } ;

/* Variables and functions */
 int ADVERTISED_Asym_Pause ; 
 int ADVERTISED_Pause ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 

__attribute__((used)) static void hclge_get_flowctrl_adv(struct hnae3_handle *handle,
				   u32 *flowctrl_adv)
{
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hclge_dev *hdev = vport->back;
	struct phy_device *phydev = hdev->hw.mac.phydev;

	if (!phydev)
		return;

	*flowctrl_adv |= (phydev->advertising & ADVERTISED_Pause) |
			 (phydev->advertising & ADVERTISED_Asym_Pause);
}