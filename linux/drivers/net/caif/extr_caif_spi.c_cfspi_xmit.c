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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* flowctrl ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {scalar_t__ qlen; } ;
struct cfspi {int flow_off_sent; scalar_t__ qd_high_mark; int /*<<< orphan*/  ndev; TYPE_1__ cfdev; TYPE_2__ qhead; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SPI_XFER ; 
 struct cfspi* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  skb_queue_tail (TYPE_2__*,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cfspi_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct cfspi *cfspi = NULL;
	unsigned long flags;
	if (!dev)
		return -EINVAL;

	cfspi = netdev_priv(dev);

	skb_queue_tail(&cfspi->qhead, skb);

	spin_lock_irqsave(&cfspi->lock, flags);
	if (!test_and_set_bit(SPI_XFER, &cfspi->state)) {
		/* Wake up xfer thread. */
		wake_up_interruptible(&cfspi->wait);
	}
	spin_unlock_irqrestore(&cfspi->lock, flags);

	/* Send flow off if number of bytes is above high water mark */
	if (!cfspi->flow_off_sent &&
		cfspi->qhead.qlen > cfspi->qd_high_mark &&
		cfspi->cfdev.flowctrl) {
		cfspi->flow_off_sent = 1;
		cfspi->cfdev.flowctrl(cfspi->ndev, 0);
	}

	return 0;
}