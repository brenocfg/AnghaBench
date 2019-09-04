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
typedef  int u16 ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct capidev {int /*<<< orphan*/  lock; int /*<<< orphan*/  recvwait; int /*<<< orphan*/  recvqueue; } ;
struct capi20_appl {struct capidev* private; } ;

/* Variables and functions */
 scalar_t__ CAPIMSG_CMD (int /*<<< orphan*/ ) ; 
 scalar_t__ CAPIMSG_COMMAND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAPIMSG_NCCI (int /*<<< orphan*/ ) ; 
 int CAPIMSG_U16 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ CAPI_CONNECT_B3_CONF ; 
 scalar_t__ CAPI_CONNECT_B3_IND ; 
 scalar_t__ CAPI_DATA_B3 ; 
 int /*<<< orphan*/  capincci_alloc (struct capidev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void capi_recv_message(struct capi20_appl *ap, struct sk_buff *skb)
{
	struct capidev *cdev = ap->private;
#ifdef CONFIG_ISDN_CAPI_MIDDLEWARE
	struct capiminor *mp;
	u16 datahandle;
	struct capincci *np;
#endif /* CONFIG_ISDN_CAPI_MIDDLEWARE */

	mutex_lock(&cdev->lock);

	if (CAPIMSG_CMD(skb->data) == CAPI_CONNECT_B3_CONF) {
		u16 info = CAPIMSG_U16(skb->data, 12); // Info field
		if ((info & 0xff00) == 0)
			capincci_alloc(cdev, CAPIMSG_NCCI(skb->data));
	}
	if (CAPIMSG_CMD(skb->data) == CAPI_CONNECT_B3_IND)
		capincci_alloc(cdev, CAPIMSG_NCCI(skb->data));

	if (CAPIMSG_COMMAND(skb->data) != CAPI_DATA_B3) {
		skb_queue_tail(&cdev->recvqueue, skb);
		wake_up_interruptible(&cdev->recvwait);
		goto unlock_out;
	}

#ifndef CONFIG_ISDN_CAPI_MIDDLEWARE
	skb_queue_tail(&cdev->recvqueue, skb);
	wake_up_interruptible(&cdev->recvwait);

#else /* CONFIG_ISDN_CAPI_MIDDLEWARE */

	np = capincci_find(cdev, CAPIMSG_CONTROL(skb->data));
	if (!np) {
		printk(KERN_ERR "BUG: capi_signal: ncci not found\n");
		skb_queue_tail(&cdev->recvqueue, skb);
		wake_up_interruptible(&cdev->recvwait);
		goto unlock_out;
	}

	mp = np->minorp;
	if (!mp) {
		skb_queue_tail(&cdev->recvqueue, skb);
		wake_up_interruptible(&cdev->recvwait);
		goto unlock_out;
	}
	if (CAPIMSG_SUBCOMMAND(skb->data) == CAPI_IND) {
		datahandle = CAPIMSG_U16(skb->data, CAPIMSG_BASELEN + 4 + 4 + 2);
		pr_debug("capi_signal: DATA_B3_IND %u len=%d\n",
			 datahandle, skb->len-CAPIMSG_LEN(skb->data));
		skb_queue_tail(&mp->inqueue, skb);

		handle_minor_recv(mp);

	} else if (CAPIMSG_SUBCOMMAND(skb->data) == CAPI_CONF) {

		datahandle = CAPIMSG_U16(skb->data, CAPIMSG_BASELEN + 4);
		pr_debug("capi_signal: DATA_B3_CONF %u 0x%x\n",
			 datahandle,
			 CAPIMSG_U16(skb->data, CAPIMSG_BASELEN + 4 + 2));
		kfree_skb(skb);
		capiminor_del_ack(mp, datahandle);
		tty_port_tty_wakeup(&mp->port);
		handle_minor_send(mp);

	} else {
		/* ups, let capi application handle it :-) */
		skb_queue_tail(&cdev->recvqueue, skb);
		wake_up_interruptible(&cdev->recvwait);
	}
#endif /* CONFIG_ISDN_CAPI_MIDDLEWARE */

unlock_out:
	mutex_unlock(&cdev->lock);
}