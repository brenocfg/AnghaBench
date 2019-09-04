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
struct net_device {int* dev_addr; } ;
struct emac_board_info {scalar_t__ membase; } ;

/* Variables and functions */
 scalar_t__ EMAC_INT_CTL_REG ; 
 scalar_t__ EMAC_INT_STA_REG ; 
 scalar_t__ EMAC_MAC_A0_REG ; 
 scalar_t__ EMAC_MAC_A1_REG ; 
 scalar_t__ EMAC_MAC_CTL0_REG ; 
 unsigned int EMAC_MAC_CTL0_SOFT_RESET ; 
 scalar_t__ EMAC_MAC_MCFG_REG ; 
 scalar_t__ EMAC_RX_CTL_REG ; 
 scalar_t__ EMAC_RX_FBC_REG ; 
 int /*<<< orphan*/  emac_setup (struct net_device*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 struct emac_board_info* netdev_priv (struct net_device*) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static unsigned int emac_powerup(struct net_device *ndev)
{
	struct emac_board_info *db = netdev_priv(ndev);
	unsigned int reg_val;

	/* initial EMAC */
	/* flush RX FIFO */
	reg_val = readl(db->membase + EMAC_RX_CTL_REG);
	reg_val |= 0x8;
	writel(reg_val, db->membase + EMAC_RX_CTL_REG);
	udelay(1);

	/* initial MAC */
	/* soft reset MAC */
	reg_val = readl(db->membase + EMAC_MAC_CTL0_REG);
	reg_val &= ~EMAC_MAC_CTL0_SOFT_RESET;
	writel(reg_val, db->membase + EMAC_MAC_CTL0_REG);

	/* set MII clock */
	reg_val = readl(db->membase + EMAC_MAC_MCFG_REG);
	reg_val &= (~(0xf << 2));
	reg_val |= (0xD << 2);
	writel(reg_val, db->membase + EMAC_MAC_MCFG_REG);

	/* clear RX counter */
	writel(0x0, db->membase + EMAC_RX_FBC_REG);

	/* disable all interrupt and clear interrupt status */
	writel(0, db->membase + EMAC_INT_CTL_REG);
	reg_val = readl(db->membase + EMAC_INT_STA_REG);
	writel(reg_val, db->membase + EMAC_INT_STA_REG);

	udelay(1);

	/* set up EMAC */
	emac_setup(ndev);

	/* set mac_address to chip */
	writel(ndev->dev_addr[0] << 16 | ndev->dev_addr[1] << 8 | ndev->
	       dev_addr[2], db->membase + EMAC_MAC_A1_REG);
	writel(ndev->dev_addr[3] << 16 | ndev->dev_addr[4] << 8 | ndev->
	       dev_addr[5], db->membase + EMAC_MAC_A0_REG);

	mdelay(1);

	return 0;
}