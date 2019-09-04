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
struct edp_phy {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ REG_EDP_PHY_GLB_MISC9 ; 
 scalar_t__ REG_EDP_PHY_GLB_VM_CFG0 ; 
 scalar_t__ REG_EDP_PHY_GLB_VM_CFG1 ; 
 int /*<<< orphan*/  edp_write (scalar_t__,int) ; 

void msm_edp_phy_vm_pe_init(struct edp_phy *phy)
{
	edp_write(phy->base + REG_EDP_PHY_GLB_VM_CFG0, 0x3);
	edp_write(phy->base + REG_EDP_PHY_GLB_VM_CFG1, 0x64);
	edp_write(phy->base + REG_EDP_PHY_GLB_MISC9, 0x6c);
}