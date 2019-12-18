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
struct emac_board_info {int emacrx_completed_flag; int /*<<< orphan*/  lock; scalar_t__ membase; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ EMAC_INT_CTL_REG ; 
 scalar_t__ EMAC_INT_STA_REG ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  emac_rx (struct net_device*) ; 
 int /*<<< orphan*/  emac_tx_done (struct net_device*,struct emac_board_info*,int) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int) ; 
 struct emac_board_info* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_intr (struct emac_board_info*) ; 
 void* readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t emac_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = dev_id;
	struct emac_board_info *db = netdev_priv(dev);
	int int_status;
	unsigned long flags;
	unsigned int reg_val;

	/* A real interrupt coming */

	/* holders of db->lock must always block IRQs */
	spin_lock_irqsave(&db->lock, flags);

	/* Disable all interrupts */
	writel(0, db->membase + EMAC_INT_CTL_REG);

	/* Got EMAC interrupt status */
	/* Got ISR */
	int_status = readl(db->membase + EMAC_INT_STA_REG);
	/* Clear ISR status */
	writel(int_status, db->membase + EMAC_INT_STA_REG);

	if (netif_msg_intr(db))
		dev_dbg(db->dev, "emac interrupt %02x\n", int_status);

	/* Received the coming packet */
	if ((int_status & 0x100) && (db->emacrx_completed_flag == 1)) {
		/* carrier lost */
		db->emacrx_completed_flag = 0;
		emac_rx(dev);
	}

	/* Transmit Interrupt check */
	if (int_status & (0x01 | 0x02))
		emac_tx_done(dev, db, int_status);

	if (int_status & (0x04 | 0x08))
		netdev_info(dev, " ab : %x\n", int_status);

	/* Re-enable interrupt mask */
	if (db->emacrx_completed_flag == 1) {
		reg_val = readl(db->membase + EMAC_INT_CTL_REG);
		reg_val |= (0xf << 0) | (0x01 << 8);
		writel(reg_val, db->membase + EMAC_INT_CTL_REG);
	}
	spin_unlock_irqrestore(&db->lock, flags);

	return IRQ_HANDLED;
}