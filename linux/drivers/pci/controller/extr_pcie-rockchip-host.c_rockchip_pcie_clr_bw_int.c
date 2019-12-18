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
typedef  int u32 ;
struct rockchip_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_RC_CONFIG_LCS ; 
 int PCI_EXP_LNKSTA_LABS ; 
 int PCI_EXP_LNKSTA_LBMS ; 
 int rockchip_pcie_read (struct rockchip_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rockchip_pcie_write (struct rockchip_pcie*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rockchip_pcie_clr_bw_int(struct rockchip_pcie *rockchip)
{
	u32 status;

	status = rockchip_pcie_read(rockchip, PCIE_RC_CONFIG_LCS);
	status |= (PCI_EXP_LNKSTA_LBMS | PCI_EXP_LNKSTA_LABS) << 16;
	rockchip_pcie_write(rockchip, status, PCIE_RC_CONFIG_LCS);
}