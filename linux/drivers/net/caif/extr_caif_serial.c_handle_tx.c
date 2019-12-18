#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {TYPE_1__* ops; } ;
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* flowctrl ) (TYPE_4__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_11__ {scalar_t__ qlen; } ;
struct ser_device {int tx_started; int /*<<< orphan*/  state; TYPE_4__* dev; TYPE_3__ common; TYPE_5__ head; struct tty_struct* tty; } ;
struct TYPE_8__ {int tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct TYPE_10__ {TYPE_2__ stats; } ;
struct TYPE_7__ {int (* write ) (struct tty_struct*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CAIF_FLOW_OFF_SENT ; 
 int /*<<< orphan*/  CAIF_SENDING ; 
 int /*<<< orphan*/  ON ; 
 scalar_t__ SEND_QUEUE_LOW ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_consume_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  ldisc_receive (struct tty_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ser_loop ; 
 int ser_write_chunk ; 
 struct sk_buff* skb_dequeue (TYPE_5__*) ; 
 struct sk_buff* skb_peek (TYPE_5__*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int stub1 (struct tty_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int tty_write_room (struct tty_struct*) ; 
 int /*<<< orphan*/  update_tty_status (struct ser_device*) ; 

__attribute__((used)) static int handle_tx(struct ser_device *ser)
{
	struct tty_struct *tty;
	struct sk_buff *skb;
	int tty_wr, len, room;

	tty = ser->tty;
	ser->tx_started = true;

	/* Enter critical section */
	if (test_and_set_bit(CAIF_SENDING, &ser->state))
		return 0;

	/* skb_peek is safe because handle_tx is called after skb_queue_tail */
	while ((skb = skb_peek(&ser->head)) != NULL) {

		/* Make sure you don't write too much */
		len = skb->len;
		room = tty_write_room(tty);
		if (!room)
			break;
		if (room > ser_write_chunk)
			room = ser_write_chunk;
		if (len > room)
			len = room;

		/* Write to tty or loopback */
		if (!ser_loop) {
			tty_wr = tty->ops->write(tty, skb->data, len);
			update_tty_status(ser);
		} else {
			tty_wr = len;
			ldisc_receive(tty, skb->data, NULL, len);
		}
		ser->dev->stats.tx_packets++;
		ser->dev->stats.tx_bytes += tty_wr;

		/* Error on TTY ?! */
		if (tty_wr < 0)
			goto error;
		/* Reduce buffer written, and discard if empty */
		skb_pull(skb, tty_wr);
		if (skb->len == 0) {
			struct sk_buff *tmp = skb_dequeue(&ser->head);
			WARN_ON(tmp != skb);
			dev_consume_skb_any(skb);
		}
	}
	/* Send flow off if queue is empty */
	if (ser->head.qlen <= SEND_QUEUE_LOW &&
		test_and_clear_bit(CAIF_FLOW_OFF_SENT, &ser->state) &&
		ser->common.flowctrl != NULL)
				ser->common.flowctrl(ser->dev, ON);
	clear_bit(CAIF_SENDING, &ser->state);
	return 0;
error:
	clear_bit(CAIF_SENDING, &ser->state);
	return tty_wr;
}