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
 int /*<<< orphan*/  PCIE_CORE_OB_REGION_ADDR0 ; 
 int /*<<< orphan*/  PCIE_CORE_OB_REGION_ADDR1 ; 
 int /*<<< orphan*/  PCIE_CORE_OB_REGION_DESC0 ; 
 int /*<<< orphan*/  PCIE_CORE_OB_REGION_DESC1 ; 
 int /*<<< orphan*/  PCIE_RC_BAR_CONF ; 
 int RC_REGION_0_ADDR_TRANS_H ; 
 int RC_REGION_0_ADDR_TRANS_L ; 
 int RC_REGION_0_PASS_BITS ; 
 int RC_REGION_0_TYPE_MASK ; 
 int rockchip_pcie_read (struct rockchip_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rockchip_pcie_write (struct rockchip_pcie*,int,int /*<<< orphan*/ ) ; 

void rockchip_pcie_cfg_configuration_accesses(
		struct rockchip_pcie *rockchip, u32 type)
{
	u32 ob_desc_0;

	/* Configuration Accesses for region 0 */
	rockchip_pcie_write(rockchip, 0x0, PCIE_RC_BAR_CONF);

	rockchip_pcie_write(rockchip,
			    (RC_REGION_0_ADDR_TRANS_L + RC_REGION_0_PASS_BITS),
			    PCIE_CORE_OB_REGION_ADDR0);
	rockchip_pcie_write(rockchip, RC_REGION_0_ADDR_TRANS_H,
			    PCIE_CORE_OB_REGION_ADDR1);
	ob_desc_0 = rockchip_pcie_read(rockchip, PCIE_CORE_OB_REGION_DESC0);
	ob_desc_0 &= ~(RC_REGION_0_TYPE_MASK);
	ob_desc_0 |= (type | (0x1 << 23));
	rockchip_pcie_write(rockchip, ob_desc_0, PCIE_CORE_OB_REGION_DESC0);
	rockchip_pcie_write(rockchip, 0x0, PCIE_CORE_OB_REGION_DESC1);
}