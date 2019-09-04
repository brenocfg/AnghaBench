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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  rx_dropped; } ;
struct net_device {TYPE_1__ stats; int /*<<< orphan*/  dev; } ;
struct ethoc {int /*<<< orphan*/  napi; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MASK ; 
 int INT_MASK_BUSY ; 
 int INT_MASK_RX ; 
 int INT_MASK_TX ; 
 int /*<<< orphan*/  INT_SOURCE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ethoc_ack_irq (struct ethoc*,int) ; 
 int /*<<< orphan*/  ethoc_disable_irq (struct ethoc*,int) ; 
 int ethoc_read (struct ethoc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 struct ethoc* netdev_priv (struct net_device*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t ethoc_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = dev_id;
	struct ethoc *priv = netdev_priv(dev);
	u32 pending;
	u32 mask;

	/* Figure out what triggered the interrupt...
	 * The tricky bit here is that the interrupt source bits get
	 * set in INT_SOURCE for an event regardless of whether that
	 * event is masked or not.  Thus, in order to figure out what
	 * triggered the interrupt, we need to remove the sources
	 * for all events that are currently masked.  This behaviour
	 * is not particularly well documented but reasonable...
	 */
	mask = ethoc_read(priv, INT_MASK);
	pending = ethoc_read(priv, INT_SOURCE);
	pending &= mask;

	if (unlikely(pending == 0))
		return IRQ_NONE;

	ethoc_ack_irq(priv, pending);

	/* We always handle the dropped packet interrupt */
	if (pending & INT_MASK_BUSY) {
		dev_dbg(&dev->dev, "packet dropped\n");
		dev->stats.rx_dropped++;
	}

	/* Handle receive/transmit event by switching to polling */
	if (pending & (INT_MASK_TX | INT_MASK_RX)) {
		ethoc_disable_irq(priv, INT_MASK_TX | INT_MASK_RX);
		napi_schedule(&priv->napi);
	}

	return IRQ_HANDLED;
}