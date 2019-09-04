#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct TYPE_9__ {scalar_t__ flex10_enable; } ;
struct TYPE_8__ {int /*<<< orphan*/  addr; } ;
struct i40e_hw {int partition_id; TYPE_4__ func_caps; TYPE_3__ mac; } ;
struct i40e_pf {size_t lan_vsi; TYPE_5__* pdev; TYPE_2__** vsi; struct i40e_hw hw; } ;
typedef  scalar_t__ i40e_status ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {TYPE_1__* netdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int I40E_AQC_MC_MAG_EN ; 
 int I40E_AQC_WOL_PRESERVE_ON_PFR ; 
 int I40E_AQC_WRITE_TYPE_LAA_ONLY ; 
 int I40E_AQC_WRITE_TYPE_LAA_WOL ; 
 int I40E_AQC_WRITE_TYPE_UPDATE_MC_MAG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ i40e_aq_mac_address_write (struct i40e_hw*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i40e_enable_mc_magic_wake(struct i40e_pf *pf)
{
	struct i40e_hw *hw = &pf->hw;
	i40e_status ret;
	u8 mac_addr[6];
	u16 flags = 0;

	/* Get current MAC address in case it's an LAA */
	if (pf->vsi[pf->lan_vsi] && pf->vsi[pf->lan_vsi]->netdev) {
		ether_addr_copy(mac_addr,
				pf->vsi[pf->lan_vsi]->netdev->dev_addr);
	} else {
		dev_err(&pf->pdev->dev,
			"Failed to retrieve MAC address; using default\n");
		ether_addr_copy(mac_addr, hw->mac.addr);
	}

	/* The FW expects the mac address write cmd to first be called with
	 * one of these flags before calling it again with the multicast
	 * enable flags.
	 */
	flags = I40E_AQC_WRITE_TYPE_LAA_WOL;

	if (hw->func_caps.flex10_enable && hw->partition_id != 1)
		flags = I40E_AQC_WRITE_TYPE_LAA_ONLY;

	ret = i40e_aq_mac_address_write(hw, flags, mac_addr, NULL);
	if (ret) {
		dev_err(&pf->pdev->dev,
			"Failed to update MAC address registers; cannot enable Multicast Magic packet wake up");
		return;
	}

	flags = I40E_AQC_MC_MAG_EN
			| I40E_AQC_WOL_PRESERVE_ON_PFR
			| I40E_AQC_WRITE_TYPE_UPDATE_MC_MAG;
	ret = i40e_aq_mac_address_write(hw, flags, mac_addr, NULL);
	if (ret)
		dev_err(&pf->pdev->dev,
			"Failed to enable Multicast Magic Packet wake up\n");
}