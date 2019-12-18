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
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  irq; } ;
struct board_info {int /*<<< orphan*/  phy_poll; int /*<<< orphan*/  mii; scalar_t__ dbug_cnt; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM9000_GPR ; 
 int EAGAIN ; 
 unsigned int IRQF_SHARED ; 
 unsigned int IRQF_TRIGGER_NONE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dm9000_init_dm9000 (struct net_device*) ; 
 int /*<<< orphan*/  dm9000_interrupt ; 
 int /*<<< orphan*/  dm9000_unmask_interrupts (struct board_info*) ; 
 int /*<<< orphan*/  iow (struct board_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int irq_get_trigger_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mii_check_media (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct board_info* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_ifup (struct board_info*) ; 
 int /*<<< orphan*/  netif_msg_link (struct board_info*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
dm9000_open(struct net_device *dev)
{
	struct board_info *db = netdev_priv(dev);
	unsigned int irq_flags = irq_get_trigger_type(dev->irq);

	if (netif_msg_ifup(db))
		dev_dbg(db->dev, "enabling %s\n", dev->name);

	/* If there is no IRQ type specified, tell the user that this is a
	 * problem
	 */
	if (irq_flags == IRQF_TRIGGER_NONE)
		dev_warn(db->dev, "WARNING: no IRQ resource flags set.\n");

	irq_flags |= IRQF_SHARED;

	/* GPIO0 on pre-activate PHY, Reg 1F is not set by reset */
	iow(db, DM9000_GPR, 0);	/* REG_1F bit0 activate phyxcer */
	mdelay(1); /* delay needs by DM9000B */

	/* Initialize DM9000 board */
	dm9000_init_dm9000(dev);

	if (request_irq(dev->irq, dm9000_interrupt, irq_flags, dev->name, dev))
		return -EAGAIN;
	/* Now that we have an interrupt handler hooked up we can unmask
	 * our interrupts
	 */
	dm9000_unmask_interrupts(db);

	/* Init driver variable */
	db->dbug_cnt = 0;

	mii_check_media(&db->mii, netif_msg_link(db), 1);
	netif_start_queue(dev);

	/* Poll initial link status */
	schedule_delayed_work(&db->phy_poll, 1);

	return 0;
}