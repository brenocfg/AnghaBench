#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct port_info {struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct ethtool_regs {int version; } ;
struct TYPE_2__ {int rev; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_CPL_MAP_TBL_DATA ; 
 int /*<<< orphan*/  A_CPL_SWITCH_CNTRL ; 
 int /*<<< orphan*/  A_MPS_INT_CAUSE ; 
 int /*<<< orphan*/  A_SG_HI_DRB_HI_THRSH ; 
 int /*<<< orphan*/  A_SG_RSPQ_CREDIT_RETURN ; 
 int /*<<< orphan*/  A_SMB_GLOBAL_TIME_CFG ; 
 int /*<<< orphan*/  A_ULPRX_PBL_ULIMIT ; 
 int /*<<< orphan*/  A_ULPTX_CONFIG ; 
 int /*<<< orphan*/  A_XGM_RX_SPI4_SOP_EOP_CNT ; 
 int /*<<< orphan*/  A_XGM_SERDES_STAT3 ; 
 int /*<<< orphan*/  A_XGM_SERDES_STATUS0 ; 
 int /*<<< orphan*/  T3_REGMAP_SIZE ; 
 int /*<<< orphan*/  XGM_REG (int /*<<< orphan*/ ,int) ; 
 int is_pcie (struct adapter*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  reg_block_dump (struct adapter*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_regs(struct net_device *dev, struct ethtool_regs *regs,
		     void *buf)
{
	struct port_info *pi = netdev_priv(dev);
	struct adapter *ap = pi->adapter;

	/*
	 * Version scheme:
	 * bits 0..9: chip version
	 * bits 10..15: chip revision
	 * bit 31: set for PCIe cards
	 */
	regs->version = 3 | (ap->params.rev << 10) | (is_pcie(ap) << 31);

	/*
	 * We skip the MAC statistics registers because they are clear-on-read.
	 * Also reading multi-register stats would need to synchronize with the
	 * periodic mac stats accumulation.  Hard to justify the complexity.
	 */
	memset(buf, 0, T3_REGMAP_SIZE);
	reg_block_dump(ap, buf, 0, A_SG_RSPQ_CREDIT_RETURN);
	reg_block_dump(ap, buf, A_SG_HI_DRB_HI_THRSH, A_ULPRX_PBL_ULIMIT);
	reg_block_dump(ap, buf, A_ULPTX_CONFIG, A_MPS_INT_CAUSE);
	reg_block_dump(ap, buf, A_CPL_SWITCH_CNTRL, A_CPL_MAP_TBL_DATA);
	reg_block_dump(ap, buf, A_SMB_GLOBAL_TIME_CFG, A_XGM_SERDES_STAT3);
	reg_block_dump(ap, buf, A_XGM_SERDES_STATUS0,
		       XGM_REG(A_XGM_SERDES_STAT3, 1));
	reg_block_dump(ap, buf, XGM_REG(A_XGM_SERDES_STATUS0, 1),
		       XGM_REG(A_XGM_RX_SPI4_SOP_EOP_CNT, 1));
}