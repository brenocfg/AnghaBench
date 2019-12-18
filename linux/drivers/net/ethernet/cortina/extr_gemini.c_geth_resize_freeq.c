#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct net_device {scalar_t__ dev_id; } ;
struct gemini_ethernet_port {int rxq_order; struct net_device* netdev; struct gemini_ethernet* geth; } ;
struct gemini_ethernet {unsigned int freeq_order; int /*<<< orphan*/  irq_lock; scalar_t__ base; scalar_t__ freeq_ring; int /*<<< orphan*/  dev; TYPE_2__* port0; TYPE_1__* port1; } ;
struct TYPE_4__ {struct net_device* netdev; } ;
struct TYPE_3__ {struct net_device* netdev; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ GLOBAL_INTERRUPT_ENABLE_4_REG ; 
 int /*<<< orphan*/  SWFQ_EMPTY_INT_BIT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  geth_cleanup_freeq (struct gemini_ethernet*) ; 
 int geth_setup_freeq (struct gemini_ethernet*) ; 
 scalar_t__ ilog2 (unsigned int) ; 
 unsigned int min (int,scalar_t__) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,scalar_t__,int,int) ; 
 struct gemini_ethernet_port* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int geth_resize_freeq(struct gemini_ethernet_port *port)
{
	struct gemini_ethernet *geth = port->geth;
	struct net_device *netdev = port->netdev;
	struct gemini_ethernet_port *other_port;
	struct net_device *other_netdev;
	unsigned int new_size = 0;
	unsigned int new_order;
	unsigned long flags;
	u32 en;
	int ret;

	if (netdev->dev_id == 0)
		other_netdev = geth->port1->netdev;
	else
		other_netdev = geth->port0->netdev;

	if (other_netdev && netif_running(other_netdev))
		return -EBUSY;

	new_size = 1 << (port->rxq_order + 1);
	netdev_dbg(netdev, "port %d size: %d order %d\n",
		   netdev->dev_id,
		   new_size,
		   port->rxq_order);
	if (other_netdev) {
		other_port = netdev_priv(other_netdev);
		new_size += 1 << (other_port->rxq_order + 1);
		netdev_dbg(other_netdev, "port %d size: %d order %d\n",
			   other_netdev->dev_id,
			   (1 << (other_port->rxq_order + 1)),
			   other_port->rxq_order);
	}

	new_order = min(15, ilog2(new_size - 1) + 1);
	dev_dbg(geth->dev, "set shared queue to size %d order %d\n",
		new_size, new_order);
	if (geth->freeq_order == new_order)
		return 0;

	spin_lock_irqsave(&geth->irq_lock, flags);

	/* Disable the software queue IRQs */
	en = readl(geth->base + GLOBAL_INTERRUPT_ENABLE_4_REG);
	en &= ~SWFQ_EMPTY_INT_BIT;
	writel(en, geth->base + GLOBAL_INTERRUPT_ENABLE_4_REG);
	spin_unlock_irqrestore(&geth->irq_lock, flags);

	/* Drop the old queue */
	if (geth->freeq_ring)
		geth_cleanup_freeq(geth);

	/* Allocate a new queue with the desired order */
	geth->freeq_order = new_order;
	ret = geth_setup_freeq(geth);

	/* Restart the interrupts - NOTE if this is the first resize
	 * after probe(), this is where the interrupts get turned on
	 * in the first place.
	 */
	spin_lock_irqsave(&geth->irq_lock, flags);
	en |= SWFQ_EMPTY_INT_BIT;
	writel(en, geth->base + GLOBAL_INTERRUPT_ENABLE_4_REG);
	spin_unlock_irqrestore(&geth->irq_lock, flags);

	return ret;
}