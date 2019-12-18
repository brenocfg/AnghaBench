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
struct urb {int num_sgs; int /*<<< orphan*/  sg; int /*<<< orphan*/  transfer_buffer; int /*<<< orphan*/  transfer_buffer_length; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/  sg_en; } ;
struct mt76_dev {TYPE_1__ usb; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MT_TX_SG_MAX_SIZE ; 
 int /*<<< orphan*/  sg_init_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int skb_to_sgvec (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mt76u_tx_setup_buffers(struct mt76_dev *dev, struct sk_buff *skb,
		       struct urb *urb)
{
	urb->transfer_buffer_length = skb->len;

	if (!dev->usb.sg_en) {
		urb->transfer_buffer = skb->data;
		return 0;
	}

	sg_init_table(urb->sg, MT_TX_SG_MAX_SIZE);
	urb->num_sgs = skb_to_sgvec(skb, urb->sg, 0, skb->len);
	if (!urb->num_sgs)
		return -ENOMEM;

	return urb->num_sgs;
}