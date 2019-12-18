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
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  tx_ints; int /*<<< orphan*/  rx_ints; } ;
struct tc35815_local {int /*<<< orphan*/  lock; TYPE_2__ lstats; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_dropped; } ;
struct net_device {TYPE_1__ stats; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int FATAL_ERROR_INT ; 
 int Int_IntBLEx ; 
 int Int_IntExBD ; 
 int Int_IntFDAEx ; 
 int Int_IntMacRx ; 
 int Int_IntMacTx ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 struct tc35815_local* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_rx_err (struct tc35815_local*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tc35815_fatal_error_interrupt (struct net_device*,int) ; 
 int tc35815_rx (struct net_device*,int) ; 
 int /*<<< orphan*/  tc35815_txdone (struct net_device*) ; 

__attribute__((used)) static int tc35815_do_interrupt(struct net_device *dev, u32 status, int limit)
{
	struct tc35815_local *lp = netdev_priv(dev);
	int ret = -1;

	/* Fatal errors... */
	if (status & FATAL_ERROR_INT) {
		tc35815_fatal_error_interrupt(dev, status);
		return 0;
	}
	/* recoverable errors */
	if (status & Int_IntFDAEx) {
		if (netif_msg_rx_err(lp))
			dev_warn(&dev->dev,
				 "Free Descriptor Area Exhausted (%#x).\n",
				 status);
		dev->stats.rx_dropped++;
		ret = 0;
	}
	if (status & Int_IntBLEx) {
		if (netif_msg_rx_err(lp))
			dev_warn(&dev->dev,
				 "Buffer List Exhausted (%#x).\n",
				 status);
		dev->stats.rx_dropped++;
		ret = 0;
	}
	if (status & Int_IntExBD) {
		if (netif_msg_rx_err(lp))
			dev_warn(&dev->dev,
				 "Excessive Buffer Descriptors (%#x).\n",
				 status);
		dev->stats.rx_length_errors++;
		ret = 0;
	}

	/* normal notification */
	if (status & Int_IntMacRx) {
		/* Got a packet(s). */
		ret = tc35815_rx(dev, limit);
		lp->lstats.rx_ints++;
	}
	if (status & Int_IntMacTx) {
		/* Transmit complete. */
		lp->lstats.tx_ints++;
		spin_lock_irq(&lp->lock);
		tc35815_txdone(dev);
		spin_unlock_irq(&lp->lock);
		if (ret < 0)
			ret = 0;
	}
	return ret;
}