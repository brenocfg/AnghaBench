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
struct i2400m {int /*<<< orphan*/  tx_lock; } ;
struct i2400mu {int /*<<< orphan*/ * tx_kthread; int /*<<< orphan*/  tx_wq; TYPE_1__* usb_iface; struct i2400m i2400m; } ;
struct i2400m_msg_hdr {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * current ; 
 int /*<<< orphan*/  d_dump (int,struct device*,struct i2400m_msg_hdr*,size_t) ; 
 int /*<<< orphan*/  d_fnend (int,struct device*,char*,struct i2400mu*) ; 
 int /*<<< orphan*/  d_fnstart (int,struct device*,char*,struct i2400mu*) ; 
 int /*<<< orphan*/  d_printf (int,struct device*,char*,...) ; 
 struct i2400m_msg_hdr* i2400m_tx_msg_get (struct i2400m*,size_t*) ; 
 int /*<<< orphan*/  i2400m_tx_msg_sent (struct i2400m*) ; 
 int /*<<< orphan*/  i2400mu_tx (struct i2400mu*,struct i2400m_msg_hdr*,size_t) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static
int i2400mu_txd(void *_i2400mu)
{
	struct i2400mu *i2400mu = _i2400mu;
	struct i2400m *i2400m = &i2400mu->i2400m;
	struct device *dev = &i2400mu->usb_iface->dev;
	struct i2400m_msg_hdr *tx_msg;
	size_t tx_msg_size;
	unsigned long flags;

	d_fnstart(4, dev, "(i2400mu %p)\n", i2400mu);

	spin_lock_irqsave(&i2400m->tx_lock, flags);
	BUG_ON(i2400mu->tx_kthread != NULL);
	i2400mu->tx_kthread = current;
	spin_unlock_irqrestore(&i2400m->tx_lock, flags);

	while (1) {
		d_printf(2, dev, "TX: waiting for messages\n");
		tx_msg = NULL;
		wait_event_interruptible(
			i2400mu->tx_wq,
			(kthread_should_stop()	/* check this first! */
			 || (tx_msg = i2400m_tx_msg_get(i2400m, &tx_msg_size)))
			);
		if (kthread_should_stop())
			break;
		WARN_ON(tx_msg == NULL);	/* should not happen...*/
		d_printf(2, dev, "TX: submitting %zu bytes\n", tx_msg_size);
		d_dump(5, dev, tx_msg, tx_msg_size);
		/* Yeah, we ignore errors ... not much we can do */
		i2400mu_tx(i2400mu, tx_msg, tx_msg_size);
		i2400m_tx_msg_sent(i2400m);	/* ack it, advance the FIFO */
	}

	spin_lock_irqsave(&i2400m->tx_lock, flags);
	i2400mu->tx_kthread = NULL;
	spin_unlock_irqrestore(&i2400m->tx_lock, flags);

	d_fnend(4, dev, "(i2400mu %p)\n", i2400mu);
	return 0;
}