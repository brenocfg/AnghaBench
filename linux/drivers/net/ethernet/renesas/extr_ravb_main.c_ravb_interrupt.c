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
typedef  int u32 ;
struct ravb_private {int /*<<< orphan*/  lock; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  ISS ; 
 int ISS_CGIS ; 
 int ISS_ES ; 
 int ISS_FRS ; 
 int ISS_FTS ; 
 int ISS_MS ; 
 int ISS_TFUS ; 
 int RAVB_BE ; 
 int RAVB_NC ; 
 struct ravb_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ravb_emac_interrupt_unlocked (struct net_device*) ; 
 int /*<<< orphan*/  ravb_error_interrupt (struct net_device*) ; 
 int /*<<< orphan*/  ravb_ptp_interrupt (struct net_device*) ; 
 scalar_t__ ravb_queue_interrupt (struct net_device*,int) ; 
 int ravb_read (struct net_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ ravb_timestamp_interrupt (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t ravb_interrupt(int irq, void *dev_id)
{
	struct net_device *ndev = dev_id;
	struct ravb_private *priv = netdev_priv(ndev);
	irqreturn_t result = IRQ_NONE;
	u32 iss;

	spin_lock(&priv->lock);
	/* Get interrupt status */
	iss = ravb_read(ndev, ISS);

	/* Received and transmitted interrupts */
	if (iss & (ISS_FRS | ISS_FTS | ISS_TFUS)) {
		int q;

		/* Timestamp updated */
		if (ravb_timestamp_interrupt(ndev))
			result = IRQ_HANDLED;

		/* Network control and best effort queue RX/TX */
		for (q = RAVB_NC; q >= RAVB_BE; q--) {
			if (ravb_queue_interrupt(ndev, q))
				result = IRQ_HANDLED;
		}
	}

	/* E-MAC status summary */
	if (iss & ISS_MS) {
		ravb_emac_interrupt_unlocked(ndev);
		result = IRQ_HANDLED;
	}

	/* Error status summary */
	if (iss & ISS_ES) {
		ravb_error_interrupt(ndev);
		result = IRQ_HANDLED;
	}

	/* gPTP interrupt status summary */
	if (iss & ISS_CGIS) {
		ravb_ptp_interrupt(ndev);
		result = IRQ_HANDLED;
	}

	spin_unlock(&priv->lock);
	return result;
}