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
typedef  int u32 ;
struct TYPE_9__ {int* supported; void* phy_addr; int /*<<< orphan*/ * link_config; } ;
struct TYPE_8__ {int num_phys; int multi_phy_config; int* speed_cap_mask; TYPE_1__* phy; } ;
struct bnx2x {TYPE_4__ port; TYPE_3__ link_params; } ;
struct TYPE_10__ {TYPE_2__* port_hw_config; } ;
struct TYPE_7__ {int /*<<< orphan*/  external_phy_config2; int /*<<< orphan*/  external_phy_config; } ;
struct TYPE_6__ {int supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_DEV_INFO (char*,int,...) ; 
 int /*<<< orphan*/  BNX2X_ERR (char*,int /*<<< orphan*/ ,...) ; 
 int BP_PORT (struct bnx2x*) ; 
 scalar_t__ CHIP_IS_E3 (struct bnx2x*) ; 
 size_t EXT_PHY1 ; 
 size_t EXT_PHY2 ; 
 size_t INT_PHY ; 
 int /*<<< orphan*/  MISC_REG_WC0_CTRL_PHY_ADDR ; 
 int /*<<< orphan*/  NIG_REG_SERDES0_CTRL_PHY_ADDR ; 
 int /*<<< orphan*/  NIG_REG_XGXS0_CTRL_PHY_ADDR ; 
 int PORT_HW_CFG_PHY_SWAPPED_ENABLED ; 
 int PORT_HW_CFG_SPEED_CAPABILITY_D0_100M_FULL ; 
 int PORT_HW_CFG_SPEED_CAPABILITY_D0_100M_HALF ; 
 int PORT_HW_CFG_SPEED_CAPABILITY_D0_10G ; 
 int PORT_HW_CFG_SPEED_CAPABILITY_D0_10M_FULL ; 
 int PORT_HW_CFG_SPEED_CAPABILITY_D0_10M_HALF ; 
 int PORT_HW_CFG_SPEED_CAPABILITY_D0_1G ; 
 int PORT_HW_CFG_SPEED_CAPABILITY_D0_20G ; 
 int PORT_HW_CFG_SPEED_CAPABILITY_D0_2_5G ; 
 void* REG_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHMEM_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int SUPPORTED_10000baseT_Full ; 
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_1000baseT_Half ; 
 int SUPPORTED_100baseT_Full ; 
 int SUPPORTED_100baseT_Half ; 
 int SUPPORTED_10baseT_Full ; 
 int SUPPORTED_10baseT_Half ; 
 int SUPPORTED_20000baseKR2_Full ; 
 int SUPPORTED_2500baseX_Full ; 
#define  SWITCH_CFG_10G 129 
#define  SWITCH_CFG_1G 128 
 TYPE_5__ dev_info ; 

__attribute__((used)) static void bnx2x_link_settings_supported(struct bnx2x *bp, u32 switch_cfg)
{
	int cfg_size = 0, idx, port = BP_PORT(bp);

	/* Aggregation of supported attributes of all external phys */
	bp->port.supported[0] = 0;
	bp->port.supported[1] = 0;
	switch (bp->link_params.num_phys) {
	case 1:
		bp->port.supported[0] = bp->link_params.phy[INT_PHY].supported;
		cfg_size = 1;
		break;
	case 2:
		bp->port.supported[0] = bp->link_params.phy[EXT_PHY1].supported;
		cfg_size = 1;
		break;
	case 3:
		if (bp->link_params.multi_phy_config &
		    PORT_HW_CFG_PHY_SWAPPED_ENABLED) {
			bp->port.supported[1] =
				bp->link_params.phy[EXT_PHY1].supported;
			bp->port.supported[0] =
				bp->link_params.phy[EXT_PHY2].supported;
		} else {
			bp->port.supported[0] =
				bp->link_params.phy[EXT_PHY1].supported;
			bp->port.supported[1] =
				bp->link_params.phy[EXT_PHY2].supported;
		}
		cfg_size = 2;
		break;
	}

	if (!(bp->port.supported[0] || bp->port.supported[1])) {
		BNX2X_ERR("NVRAM config error. BAD phy config. PHY1 config 0x%x, PHY2 config 0x%x\n",
			   SHMEM_RD(bp,
			   dev_info.port_hw_config[port].external_phy_config),
			   SHMEM_RD(bp,
			   dev_info.port_hw_config[port].external_phy_config2));
		return;
	}

	if (CHIP_IS_E3(bp))
		bp->port.phy_addr = REG_RD(bp, MISC_REG_WC0_CTRL_PHY_ADDR);
	else {
		switch (switch_cfg) {
		case SWITCH_CFG_1G:
			bp->port.phy_addr = REG_RD(
				bp, NIG_REG_SERDES0_CTRL_PHY_ADDR + port*0x10);
			break;
		case SWITCH_CFG_10G:
			bp->port.phy_addr = REG_RD(
				bp, NIG_REG_XGXS0_CTRL_PHY_ADDR + port*0x18);
			break;
		default:
			BNX2X_ERR("BAD switch_cfg link_config 0x%x\n",
				  bp->port.link_config[0]);
			return;
		}
	}
	BNX2X_DEV_INFO("phy_addr 0x%x\n", bp->port.phy_addr);
	/* mask what we support according to speed_cap_mask per configuration */
	for (idx = 0; idx < cfg_size; idx++) {
		if (!(bp->link_params.speed_cap_mask[idx] &
				PORT_HW_CFG_SPEED_CAPABILITY_D0_10M_HALF))
			bp->port.supported[idx] &= ~SUPPORTED_10baseT_Half;

		if (!(bp->link_params.speed_cap_mask[idx] &
				PORT_HW_CFG_SPEED_CAPABILITY_D0_10M_FULL))
			bp->port.supported[idx] &= ~SUPPORTED_10baseT_Full;

		if (!(bp->link_params.speed_cap_mask[idx] &
				PORT_HW_CFG_SPEED_CAPABILITY_D0_100M_HALF))
			bp->port.supported[idx] &= ~SUPPORTED_100baseT_Half;

		if (!(bp->link_params.speed_cap_mask[idx] &
				PORT_HW_CFG_SPEED_CAPABILITY_D0_100M_FULL))
			bp->port.supported[idx] &= ~SUPPORTED_100baseT_Full;

		if (!(bp->link_params.speed_cap_mask[idx] &
					PORT_HW_CFG_SPEED_CAPABILITY_D0_1G))
			bp->port.supported[idx] &= ~(SUPPORTED_1000baseT_Half |
						     SUPPORTED_1000baseT_Full);

		if (!(bp->link_params.speed_cap_mask[idx] &
					PORT_HW_CFG_SPEED_CAPABILITY_D0_2_5G))
			bp->port.supported[idx] &= ~SUPPORTED_2500baseX_Full;

		if (!(bp->link_params.speed_cap_mask[idx] &
					PORT_HW_CFG_SPEED_CAPABILITY_D0_10G))
			bp->port.supported[idx] &= ~SUPPORTED_10000baseT_Full;

		if (!(bp->link_params.speed_cap_mask[idx] &
					PORT_HW_CFG_SPEED_CAPABILITY_D0_20G))
			bp->port.supported[idx] &= ~SUPPORTED_20000baseKR2_Full;
	}

	BNX2X_DEV_INFO("supported 0x%x 0x%x\n", bp->port.supported[0],
		       bp->port.supported[1]);
}