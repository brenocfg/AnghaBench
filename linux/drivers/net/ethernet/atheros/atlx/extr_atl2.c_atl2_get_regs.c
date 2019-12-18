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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct ethtool_regs {int version; } ;
struct atl2_hw {int revision_id; int device_id; } ;
struct atl2_adapter {struct atl2_hw hw; } ;

/* Variables and functions */
 scalar_t__ ATL2_READ_REG (struct atl2_hw*,scalar_t__) ; 
 int ATL2_REGS_LEN ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_BMSR ; 
 scalar_t__ REG_CMBDISDMA_TIMER ; 
 scalar_t__ REG_DESC_BASE_ADDR_HI ; 
 scalar_t__ REG_DMAR ; 
 scalar_t__ REG_DMAW ; 
 scalar_t__ REG_IDLE_STATUS ; 
 scalar_t__ REG_IMR ; 
 scalar_t__ REG_IRQ_MODU_TIMER_INIT ; 
 scalar_t__ REG_ISR ; 
 scalar_t__ REG_MAC_CTRL ; 
 scalar_t__ REG_MAC_HALF_DUPLX_CTRL ; 
 scalar_t__ REG_MAC_IPG_IFG ; 
 scalar_t__ REG_MAC_STA_ADDR ; 
 scalar_t__ REG_MANUAL_TIMER_INIT ; 
 scalar_t__ REG_MASTER_CTRL ; 
 scalar_t__ REG_MB_RXD_RD_IDX ; 
 scalar_t__ REG_MB_TXD_WR_IDX ; 
 scalar_t__ REG_MDIO_CTRL ; 
 scalar_t__ REG_MTU ; 
 scalar_t__ REG_PAUSE_OFF_TH ; 
 scalar_t__ REG_PAUSE_ON_TH ; 
 scalar_t__ REG_PCIE_DEV_MISC_CTRL ; 
 scalar_t__ REG_PHY_ENABLE ; 
 scalar_t__ REG_RXD_BASE_ADDR_LO ; 
 scalar_t__ REG_RXD_BUF_NUM ; 
 scalar_t__ REG_RX_HASH_TABLE ; 
 scalar_t__ REG_SERDES_LOCK ; 
 scalar_t__ REG_SPI_FLASH_CONFIG ; 
 scalar_t__ REG_SPI_FLASH_CTRL ; 
 scalar_t__ REG_SRAM_TXRAM_END ; 
 scalar_t__ REG_TWSI_CTRL ; 
 scalar_t__ REG_TXD_BASE_ADDR_LO ; 
 scalar_t__ REG_TXD_MEM_SIZE ; 
 scalar_t__ REG_TXS_BASE_ADDR_LO ; 
 scalar_t__ REG_TXS_MEM_SIZE ; 
 scalar_t__ REG_TX_CUT_THRESH ; 
 scalar_t__ REG_VPD_CAP ; 
 scalar_t__ REG_WOL_CTRL ; 
 int /*<<< orphan*/  atl2_read_phy_reg (struct atl2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 struct atl2_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void atl2_get_regs(struct net_device *netdev,
	struct ethtool_regs *regs, void *p)
{
	struct atl2_adapter *adapter = netdev_priv(netdev);
	struct atl2_hw *hw = &adapter->hw;
	u32 *regs_buff = p;
	u16 phy_data;

	memset(p, 0, sizeof(u32) * ATL2_REGS_LEN);

	regs->version = (1 << 24) | (hw->revision_id << 16) | hw->device_id;

	regs_buff[0]  = ATL2_READ_REG(hw, REG_VPD_CAP);
	regs_buff[1]  = ATL2_READ_REG(hw, REG_SPI_FLASH_CTRL);
	regs_buff[2]  = ATL2_READ_REG(hw, REG_SPI_FLASH_CONFIG);
	regs_buff[3]  = ATL2_READ_REG(hw, REG_TWSI_CTRL);
	regs_buff[4]  = ATL2_READ_REG(hw, REG_PCIE_DEV_MISC_CTRL);
	regs_buff[5]  = ATL2_READ_REG(hw, REG_MASTER_CTRL);
	regs_buff[6]  = ATL2_READ_REG(hw, REG_MANUAL_TIMER_INIT);
	regs_buff[7]  = ATL2_READ_REG(hw, REG_IRQ_MODU_TIMER_INIT);
	regs_buff[8]  = ATL2_READ_REG(hw, REG_PHY_ENABLE);
	regs_buff[9]  = ATL2_READ_REG(hw, REG_CMBDISDMA_TIMER);
	regs_buff[10] = ATL2_READ_REG(hw, REG_IDLE_STATUS);
	regs_buff[11] = ATL2_READ_REG(hw, REG_MDIO_CTRL);
	regs_buff[12] = ATL2_READ_REG(hw, REG_SERDES_LOCK);
	regs_buff[13] = ATL2_READ_REG(hw, REG_MAC_CTRL);
	regs_buff[14] = ATL2_READ_REG(hw, REG_MAC_IPG_IFG);
	regs_buff[15] = ATL2_READ_REG(hw, REG_MAC_STA_ADDR);
	regs_buff[16] = ATL2_READ_REG(hw, REG_MAC_STA_ADDR+4);
	regs_buff[17] = ATL2_READ_REG(hw, REG_RX_HASH_TABLE);
	regs_buff[18] = ATL2_READ_REG(hw, REG_RX_HASH_TABLE+4);
	regs_buff[19] = ATL2_READ_REG(hw, REG_MAC_HALF_DUPLX_CTRL);
	regs_buff[20] = ATL2_READ_REG(hw, REG_MTU);
	regs_buff[21] = ATL2_READ_REG(hw, REG_WOL_CTRL);
	regs_buff[22] = ATL2_READ_REG(hw, REG_SRAM_TXRAM_END);
	regs_buff[23] = ATL2_READ_REG(hw, REG_DESC_BASE_ADDR_HI);
	regs_buff[24] = ATL2_READ_REG(hw, REG_TXD_BASE_ADDR_LO);
	regs_buff[25] = ATL2_READ_REG(hw, REG_TXD_MEM_SIZE);
	regs_buff[26] = ATL2_READ_REG(hw, REG_TXS_BASE_ADDR_LO);
	regs_buff[27] = ATL2_READ_REG(hw, REG_TXS_MEM_SIZE);
	regs_buff[28] = ATL2_READ_REG(hw, REG_RXD_BASE_ADDR_LO);
	regs_buff[29] = ATL2_READ_REG(hw, REG_RXD_BUF_NUM);
	regs_buff[30] = ATL2_READ_REG(hw, REG_DMAR);
	regs_buff[31] = ATL2_READ_REG(hw, REG_TX_CUT_THRESH);
	regs_buff[32] = ATL2_READ_REG(hw, REG_DMAW);
	regs_buff[33] = ATL2_READ_REG(hw, REG_PAUSE_ON_TH);
	regs_buff[34] = ATL2_READ_REG(hw, REG_PAUSE_OFF_TH);
	regs_buff[35] = ATL2_READ_REG(hw, REG_MB_TXD_WR_IDX);
	regs_buff[36] = ATL2_READ_REG(hw, REG_MB_RXD_RD_IDX);
	regs_buff[38] = ATL2_READ_REG(hw, REG_ISR);
	regs_buff[39] = ATL2_READ_REG(hw, REG_IMR);

	atl2_read_phy_reg(hw, MII_BMCR, &phy_data);
	regs_buff[40] = (u32)phy_data;
	atl2_read_phy_reg(hw, MII_BMSR, &phy_data);
	regs_buff[41] = (u32)phy_data;
}