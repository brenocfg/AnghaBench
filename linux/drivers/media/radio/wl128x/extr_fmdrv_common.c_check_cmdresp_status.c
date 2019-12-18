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
struct sk_buff {scalar_t__ data; } ;
struct TYPE_2__ {int /*<<< orphan*/  timer; } ;
struct fmdev {TYPE_1__ irq_info; int /*<<< orphan*/  resp_skb_lock; struct sk_buff* resp_skb; } ;
struct fm_event_msg_hdr {scalar_t__ status; int /*<<< orphan*/  op; } ;

/* Variables and functions */
 scalar_t__ FM_DRV_TX_TIMEOUT ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fmerr (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline int check_cmdresp_status(struct fmdev *fmdev,
		struct sk_buff **skb)
{
	struct fm_event_msg_hdr *fm_evt_hdr;
	unsigned long flags;

	del_timer(&fmdev->irq_info.timer);

	spin_lock_irqsave(&fmdev->resp_skb_lock, flags);
	*skb = fmdev->resp_skb;
	fmdev->resp_skb = NULL;
	spin_unlock_irqrestore(&fmdev->resp_skb_lock, flags);

	fm_evt_hdr = (void *)(*skb)->data;
	if (fm_evt_hdr->status != 0) {
		fmerr("irq: opcode %x response status is not zero Initiating irq recovery process\n",
				fm_evt_hdr->op);

		mod_timer(&fmdev->irq_info.timer, jiffies + FM_DRV_TX_TIMEOUT);
		return -1;
	}

	return 0;
}