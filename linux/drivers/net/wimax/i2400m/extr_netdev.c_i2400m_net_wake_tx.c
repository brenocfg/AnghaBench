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
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct net_device {int dummy; } ;
struct i2400m {int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  wake_tx_ws; int /*<<< orphan*/  wake_tx_skb; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  d_dump (int,struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_fnend (int,struct device*,char*,struct sk_buff*,struct net_device*,int) ; 
 int /*<<< orphan*/  d_fnstart (int,struct device*,char*,struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  d_printf (int,struct device*,char*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct device* i2400m_dev (struct i2400m*) ; 
 int /*<<< orphan*/  i2400m_get (struct i2400m*) ; 
 int /*<<< orphan*/  i2400m_tx_prep_header (struct sk_buff*) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_get (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static
int i2400m_net_wake_tx(struct i2400m *i2400m, struct net_device *net_dev,
		       struct sk_buff *skb)
{
	int result;
	struct device *dev = i2400m_dev(i2400m);
	unsigned long flags;

	d_fnstart(3, dev, "(skb %p net_dev %p)\n", skb, net_dev);
	if (net_ratelimit()) {
		d_printf(3, dev, "WAKE&NETTX: "
			 "skb %p sending %d bytes to radio\n",
			 skb, skb->len);
		d_dump(4, dev, skb->data, skb->len);
	}
	/* We hold a ref count for i2400m and skb, so when
	 * stopping() the device, we need to cancel that work
	 * and if pending, release those resources. */
	result = 0;
	spin_lock_irqsave(&i2400m->tx_lock, flags);
	if (!i2400m->wake_tx_skb) {
		netif_stop_queue(net_dev);
		i2400m_get(i2400m);
		i2400m->wake_tx_skb = skb_get(skb);	/* transfer ref count */
		i2400m_tx_prep_header(skb);
		result = schedule_work(&i2400m->wake_tx_ws);
		WARN_ON(result == 0);
	}
	spin_unlock_irqrestore(&i2400m->tx_lock, flags);
	if (result == 0) {
		/* Yes, this happens even if we stopped the
		 * queue -- blame the queue disciplines that
		 * queue without looking -- I guess there is a reason
		 * for that. */
		if (net_ratelimit())
			d_printf(1, dev, "NETTX: device exiting idle, "
				 "dropping skb %p, queue running %d\n",
				 skb, netif_queue_stopped(net_dev));
		result = -EBUSY;
	}
	d_fnend(3, dev, "(skb %p net_dev %p) = %d\n", skb, net_dev, result);
	return result;
}