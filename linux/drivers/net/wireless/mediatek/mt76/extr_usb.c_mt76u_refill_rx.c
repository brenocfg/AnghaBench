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
struct urb {int /*<<< orphan*/  transfer_buffer; int /*<<< orphan*/  transfer_buffer_length; } ;
struct mt76_queue {int /*<<< orphan*/  buf_size; int /*<<< orphan*/  rx_page; } ;
struct TYPE_2__ {scalar_t__ sg_en; } ;
struct mt76_dev {TYPE_1__ usb; struct mt76_queue* q_rx; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 size_t MT_RXQ_MAIN ; 
 int mt76u_fill_rx_sg (struct mt76_dev*,struct mt76_queue*,struct urb*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_frag_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mt76u_refill_rx(struct mt76_dev *dev, struct urb *urb, int nsgs, gfp_t gfp)
{
	struct mt76_queue *q = &dev->q_rx[MT_RXQ_MAIN];

	if (dev->usb.sg_en)
		return mt76u_fill_rx_sg(dev, q, urb, nsgs, gfp);

	urb->transfer_buffer_length = q->buf_size;
	urb->transfer_buffer = page_frag_alloc(&q->rx_page, q->buf_size, gfp);

	return urb->transfer_buffer ? 0 : -ENOMEM;
}