#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct sk_buff {int len; scalar_t__ data; } ;
struct TYPE_5__ {int dmaaddr; void* dmabuf; } ;
struct TYPE_6__ {TYPE_1__ sendbuf; int /*<<< orphan*/  send_queue; } ;
typedef  TYPE_2__ avmcard_dmainfo ;
struct TYPE_7__ {int csr; scalar_t__ mbase; TYPE_2__* dma; } ;
typedef  TYPE_3__ avmcard ;

/* Variables and functions */
 scalar_t__ CAPICMD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAPIMSG_COMMAND (scalar_t__) ; 
 scalar_t__ CAPIMSG_DATALEN (scalar_t__) ; 
 scalar_t__ CAPIMSG_LEN (scalar_t__) ; 
 int /*<<< orphan*/  CAPIMSG_SUBCOMMAND (scalar_t__) ; 
 scalar_t__ CAPI_DATA_B3_REQ ; 
 int DBELL_DOWN_ARM ; 
 scalar_t__ DOORBELL ; 
 scalar_t__ MBOX_DOWN_ADDR ; 
 scalar_t__ MBOX_DOWN_LEN ; 
 int /*<<< orphan*/  SEND_DATA_B3_REQ ; 
 int /*<<< orphan*/  SEND_MESSAGE ; 
 int /*<<< orphan*/  _put_byte (void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _put_slice (void**,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  c4outmeml (scalar_t__,int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data_offset (struct sk_buff*,int,void*,int) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void c4_dispatch_tx(avmcard *card)
{
	avmcard_dmainfo *dma = card->dma;
	struct sk_buff *skb;
	u8 cmd, subcmd;
	u16 len;
	u32 txlen;
	void *p;


	if (card->csr & DBELL_DOWN_ARM) { /* tx busy */
		return;
	}

	skb = skb_dequeue(&dma->send_queue);
	if (!skb) {
#ifdef AVM_C4_DEBUG
		printk(KERN_DEBUG "%s: tx underrun\n", card->name);
#endif
		return;
	}

	len = CAPIMSG_LEN(skb->data);

	if (len) {
		cmd = CAPIMSG_COMMAND(skb->data);
		subcmd = CAPIMSG_SUBCOMMAND(skb->data);

		p = dma->sendbuf.dmabuf;

		if (CAPICMD(cmd, subcmd) == CAPI_DATA_B3_REQ) {
			u16 dlen = CAPIMSG_DATALEN(skb->data);
			_put_byte(&p, SEND_DATA_B3_REQ);
			_put_slice(&p, skb->data, len);
			_put_slice(&p, skb->data + len, dlen);
		} else {
			_put_byte(&p, SEND_MESSAGE);
			_put_slice(&p, skb->data, len);
		}
		txlen = (u8 *)p - (u8 *)dma->sendbuf.dmabuf;
#ifdef AVM_C4_DEBUG
		printk(KERN_DEBUG "%s: tx put msg len=%d\n", card->name, txlen);
#endif
	} else {
		txlen = skb->len - 2;
#ifdef AVM_C4_POLLDEBUG
		if (skb->data[2] == SEND_POLLACK)
			printk(KERN_INFO "%s: ack to c4\n", card->name);
#endif
#ifdef AVM_C4_DEBUG
		printk(KERN_DEBUG "%s: tx put 0x%x len=%d\n",
		       card->name, skb->data[2], txlen);
#endif
		skb_copy_from_linear_data_offset(skb, 2, dma->sendbuf.dmabuf,
						 skb->len - 2);
	}
	txlen = (txlen + 3) & ~3;

	c4outmeml(card->mbase + MBOX_DOWN_ADDR, dma->sendbuf.dmaaddr);
	c4outmeml(card->mbase + MBOX_DOWN_LEN, txlen);

	card->csr |= DBELL_DOWN_ARM;

	c4outmeml(card->mbase + DOORBELL, DBELL_DOWN_ARM);

	dev_kfree_skb_any(skb);
}