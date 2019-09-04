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
struct urb {int /*<<< orphan*/  status; scalar_t__ context; } ;
struct sk_buff {scalar_t__ len; scalar_t__ dev; } ;
struct bfusb_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  completed_q; int /*<<< orphan*/  pending_q; TYPE_2__* hdev; int /*<<< orphan*/  pending_tx; } ;
struct TYPE_3__ {int /*<<< orphan*/  err_tx; int /*<<< orphan*/  byte_tx; } ;
struct TYPE_4__ {TYPE_1__ stat; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct bfusb_data*,struct urb*,struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  HCI_RUNNING ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfusb_tx_wakeup (struct bfusb_data*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_unlink (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bfusb_tx_complete(struct urb *urb)
{
	struct sk_buff *skb = (struct sk_buff *) urb->context;
	struct bfusb_data *data = (struct bfusb_data *) skb->dev;

	BT_DBG("bfusb %p urb %p skb %p len %d", data, urb, skb, skb->len);

	atomic_dec(&data->pending_tx);

	if (!test_bit(HCI_RUNNING, &data->hdev->flags))
		return;

	if (!urb->status)
		data->hdev->stat.byte_tx += skb->len;
	else
		data->hdev->stat.err_tx++;

	read_lock(&data->lock);

	skb_unlink(skb, &data->pending_q);
	skb_queue_tail(&data->completed_q, skb);

	bfusb_tx_wakeup(data);

	read_unlock(&data->lock);
}