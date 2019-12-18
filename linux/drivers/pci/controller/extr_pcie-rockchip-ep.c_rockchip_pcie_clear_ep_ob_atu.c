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
typedef  int /*<<< orphan*/  u32 ;
struct rockchip_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ROCKCHIP_PCIE_AT_OB_REGION_CPU_ADDR0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ROCKCHIP_PCIE_AT_OB_REGION_CPU_ADDR1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ROCKCHIP_PCIE_AT_OB_REGION_DESC0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ROCKCHIP_PCIE_AT_OB_REGION_DESC1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ROCKCHIP_PCIE_AT_OB_REGION_PCI_ADDR0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ROCKCHIP_PCIE_AT_OB_REGION_PCI_ADDR1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rockchip_pcie_write (struct rockchip_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rockchip_pcie_clear_ep_ob_atu(struct rockchip_pcie *rockchip,
					  u32 region)
{
	rockchip_pcie_write(rockchip, 0,
			    ROCKCHIP_PCIE_AT_OB_REGION_PCI_ADDR0(region));
	rockchip_pcie_write(rockchip, 0,
			    ROCKCHIP_PCIE_AT_OB_REGION_PCI_ADDR1(region));
	rockchip_pcie_write(rockchip, 0,
			    ROCKCHIP_PCIE_AT_OB_REGION_DESC0(region));
	rockchip_pcie_write(rockchip, 0,
			    ROCKCHIP_PCIE_AT_OB_REGION_DESC1(region));
	rockchip_pcie_write(rockchip, 0,
			    ROCKCHIP_PCIE_AT_OB_REGION_CPU_ADDR0(region));
	rockchip_pcie_write(rockchip, 0,
			    ROCKCHIP_PCIE_AT_OB_REGION_CPU_ADDR1(region));
}