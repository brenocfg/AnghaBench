#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct capi_ctr {scalar_t__ driverdata; } ;
struct TYPE_4__ {int /*<<< orphan*/  ncci_head; TYPE_2__* card; } ;
typedef  TYPE_1__ avmctrl_info ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ avmcard ;

/* Variables and functions */
 int /*<<< orphan*/  CAPIMSG_APPID (int /*<<< orphan*/ ) ; 
 scalar_t__ CAPIMSG_CMD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAPIMSG_MSGID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAPIMSG_NCCI (int /*<<< orphan*/ ) ; 
 scalar_t__ CAPI_DATA_B3_REQ ; 
 scalar_t__ CAPI_NOERROR ; 
 int /*<<< orphan*/  b1dma_queue_tx (TYPE_2__*,struct sk_buff*) ; 
 scalar_t__ capilib_data_b3_req (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

u16 b1dma_send_message(struct capi_ctr *ctrl, struct sk_buff *skb)
{
	avmctrl_info *cinfo = (avmctrl_info *)(ctrl->driverdata);
	avmcard *card = cinfo->card;
	u16 retval = CAPI_NOERROR;

	if (CAPIMSG_CMD(skb->data) == CAPI_DATA_B3_REQ) {
		unsigned long flags;
		spin_lock_irqsave(&card->lock, flags);
		retval = capilib_data_b3_req(&cinfo->ncci_head,
					     CAPIMSG_APPID(skb->data),
					     CAPIMSG_NCCI(skb->data),
					     CAPIMSG_MSGID(skb->data));
		spin_unlock_irqrestore(&card->lock, flags);
	}
	if (retval == CAPI_NOERROR)
		b1dma_queue_tx(card, skb);

	return retval;
}