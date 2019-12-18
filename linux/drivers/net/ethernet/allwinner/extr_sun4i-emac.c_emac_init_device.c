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
struct emac_board_info {int /*<<< orphan*/  lock; scalar_t__ membase; } ;

/* Variables and functions */
 scalar_t__ EMAC_CTL_REG ; 
 unsigned int EMAC_CTL_RESET ; 
 unsigned int EMAC_CTL_RX_EN ; 
 unsigned int EMAC_CTL_TX_EN ; 
 scalar_t__ EMAC_INT_CTL_REG ; 
 int /*<<< orphan*/  emac_update_duplex (struct net_device*) ; 
 int /*<<< orphan*/  emac_update_speed (struct net_device*) ; 
 struct emac_board_info* netdev_priv (struct net_device*) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void emac_init_device(struct net_device *dev)
{
	struct emac_board_info *db = netdev_priv(dev);
	unsigned long flags;
	unsigned int reg_val;

	spin_lock_irqsave(&db->lock, flags);

	emac_update_speed(dev);
	emac_update_duplex(dev);

	/* enable RX/TX */
	reg_val = readl(db->membase + EMAC_CTL_REG);
	writel(reg_val | EMAC_CTL_RESET | EMAC_CTL_TX_EN | EMAC_CTL_RX_EN,
		db->membase + EMAC_CTL_REG);

	/* enable RX/TX0/RX Hlevel interrup */
	reg_val = readl(db->membase + EMAC_INT_CTL_REG);
	reg_val |= (0xf << 0) | (0x01 << 8);
	writel(reg_val, db->membase + EMAC_INT_CTL_REG);

	spin_unlock_irqrestore(&db->lock, flags);
}