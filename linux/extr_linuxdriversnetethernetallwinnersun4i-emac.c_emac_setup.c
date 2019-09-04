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
struct net_device {int dummy; } ;
struct emac_board_info {scalar_t__ membase; } ;

/* Variables and functions */
 int EMAC_MAC_CLRT_COLLISION_WINDOW ; 
 scalar_t__ EMAC_MAC_CLRT_REG ; 
 int EMAC_MAC_CLRT_RM ; 
 scalar_t__ EMAC_MAC_CTL0_REG ; 
 unsigned int EMAC_MAC_CTL0_RX_FLOW_CTL_EN ; 
 unsigned int EMAC_MAC_CTL0_TX_FLOW_CTL_EN ; 
 unsigned int EMAC_MAC_CTL1_CRC_EN ; 
 unsigned int EMAC_MAC_CTL1_LEN_CHECK_EN ; 
 unsigned int EMAC_MAC_CTL1_PAD_EN ; 
 scalar_t__ EMAC_MAC_CTL1_REG ; 
 int EMAC_MAC_IPGR_IPG1 ; 
 int EMAC_MAC_IPGR_IPG2 ; 
 scalar_t__ EMAC_MAC_IPGR_REG ; 
 int EMAC_MAC_IPGT_FULL_DUPLEX ; 
 scalar_t__ EMAC_MAC_IPGT_REG ; 
 scalar_t__ EMAC_MAC_MAXF_REG ; 
 int EMAC_MAX_FRAME_LEN ; 
 unsigned int EMAC_TX_MODE_ABORTED_FRAME_EN ; 
 scalar_t__ EMAC_TX_MODE_REG ; 
 struct emac_board_info* netdev_priv (struct net_device*) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static unsigned int emac_setup(struct net_device *ndev)
{
	struct emac_board_info *db = netdev_priv(ndev);
	unsigned int reg_val;

	/* set up TX */
	reg_val = readl(db->membase + EMAC_TX_MODE_REG);

	writel(reg_val | EMAC_TX_MODE_ABORTED_FRAME_EN,
		db->membase + EMAC_TX_MODE_REG);

	/* set MAC */
	/* set MAC CTL0 */
	reg_val = readl(db->membase + EMAC_MAC_CTL0_REG);
	writel(reg_val | EMAC_MAC_CTL0_RX_FLOW_CTL_EN |
		EMAC_MAC_CTL0_TX_FLOW_CTL_EN,
		db->membase + EMAC_MAC_CTL0_REG);

	/* set MAC CTL1 */
	reg_val = readl(db->membase + EMAC_MAC_CTL1_REG);
	reg_val |= EMAC_MAC_CTL1_LEN_CHECK_EN;
	reg_val |= EMAC_MAC_CTL1_CRC_EN;
	reg_val |= EMAC_MAC_CTL1_PAD_EN;
	writel(reg_val, db->membase + EMAC_MAC_CTL1_REG);

	/* set up IPGT */
	writel(EMAC_MAC_IPGT_FULL_DUPLEX, db->membase + EMAC_MAC_IPGT_REG);

	/* set up IPGR */
	writel((EMAC_MAC_IPGR_IPG1 << 8) | EMAC_MAC_IPGR_IPG2,
		db->membase + EMAC_MAC_IPGR_REG);

	/* set up Collison window */
	writel((EMAC_MAC_CLRT_COLLISION_WINDOW << 8) | EMAC_MAC_CLRT_RM,
		db->membase + EMAC_MAC_CLRT_REG);

	/* set up Max Frame Length */
	writel(EMAC_MAX_FRAME_LEN,
		db->membase + EMAC_MAC_MAXF_REG);

	return 0;
}