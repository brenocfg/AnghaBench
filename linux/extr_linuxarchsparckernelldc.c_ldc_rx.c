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
struct ldc_packet {int type; } ;
struct TYPE_2__ {scalar_t__ mode; } ;
struct ldc_channel {unsigned long chan_state; int rx_head; int rx_tail; scalar_t__ hs_state; int flags; int rx_num_entries; int /*<<< orphan*/  lock; struct ldc_packet* rx_base; TYPE_1__ cfg; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int LDC_ABORT (struct ldc_channel*) ; 
 unsigned long LDC_CHANNEL_UP ; 
#define  LDC_CTRL 130 
#define  LDC_DATA 129 
#define  LDC_ERR 128 
 unsigned int LDC_EVENT_DATA_READY ; 
 unsigned int LDC_EVENT_RESET ; 
 unsigned int LDC_EVENT_UP ; 
 int LDC_FLAG_RESET ; 
 scalar_t__ LDC_HS_COMPLETE ; 
 scalar_t__ LDC_MODE_RAW ; 
 int LDC_PACKET_SIZE ; 
 int /*<<< orphan*/  LDC_STATE_CONNECTED ; 
 int /*<<< orphan*/  RX ; 
 int __set_rx_head (struct ldc_channel*,unsigned long) ; 
 int /*<<< orphan*/  ldc_rx_reset (struct ldc_channel*) ; 
 int /*<<< orphan*/  ldc_set_state (struct ldc_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldcdbg (int /*<<< orphan*/ ,char*,unsigned long,unsigned long,int,int) ; 
 int process_control_frame (struct ldc_channel*,struct ldc_packet*) ; 
 int process_error_frame (struct ldc_channel*,struct ldc_packet*) ; 
 int /*<<< orphan*/  send_events (struct ldc_channel*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sun4v_ldc_rx_get_state (int /*<<< orphan*/ ,int*,int*,unsigned long*) ; 

__attribute__((used)) static irqreturn_t ldc_rx(int irq, void *dev_id)
{
	struct ldc_channel *lp = dev_id;
	unsigned long orig_state, flags;
	unsigned int event_mask;

	spin_lock_irqsave(&lp->lock, flags);

	orig_state = lp->chan_state;

	/* We should probably check for hypervisor errors here and
	 * reset the LDC channel if we get one.
	 */
	sun4v_ldc_rx_get_state(lp->id,
			       &lp->rx_head,
			       &lp->rx_tail,
			       &lp->chan_state);

	ldcdbg(RX, "RX state[0x%02lx:0x%02lx] head[0x%04lx] tail[0x%04lx]\n",
	       orig_state, lp->chan_state, lp->rx_head, lp->rx_tail);

	event_mask = 0;

	if (lp->cfg.mode == LDC_MODE_RAW &&
	    lp->chan_state == LDC_CHANNEL_UP) {
		lp->hs_state = LDC_HS_COMPLETE;
		ldc_set_state(lp, LDC_STATE_CONNECTED);

		/*
		 * Generate an LDC_EVENT_UP event if the channel
		 * was not already up.
		 */
		if (orig_state != LDC_CHANNEL_UP) {
			event_mask |= LDC_EVENT_UP;
			orig_state = lp->chan_state;
		}
	}

	/* If we are in reset state, flush the RX queue and ignore
	 * everything.
	 */
	if (lp->flags & LDC_FLAG_RESET) {
		(void) ldc_rx_reset(lp);
		goto out;
	}

	/* Once we finish the handshake, we let the ldc_read()
	 * paths do all of the control frame and state management.
	 * Just trigger the callback.
	 */
	if (lp->hs_state == LDC_HS_COMPLETE) {
handshake_complete:
		if (lp->chan_state != orig_state) {
			unsigned int event = LDC_EVENT_RESET;

			if (lp->chan_state == LDC_CHANNEL_UP)
				event = LDC_EVENT_UP;

			event_mask |= event;
		}
		if (lp->rx_head != lp->rx_tail)
			event_mask |= LDC_EVENT_DATA_READY;

		goto out;
	}

	if (lp->chan_state != orig_state)
		goto out;

	while (lp->rx_head != lp->rx_tail) {
		struct ldc_packet *p;
		unsigned long new;
		int err;

		p = lp->rx_base + (lp->rx_head / LDC_PACKET_SIZE);

		switch (p->type) {
		case LDC_CTRL:
			err = process_control_frame(lp, p);
			if (err > 0)
				event_mask |= err;
			break;

		case LDC_DATA:
			event_mask |= LDC_EVENT_DATA_READY;
			err = 0;
			break;

		case LDC_ERR:
			err = process_error_frame(lp, p);
			break;

		default:
			err = LDC_ABORT(lp);
			break;
		}

		if (err < 0)
			break;

		new = lp->rx_head;
		new += LDC_PACKET_SIZE;
		if (new == (lp->rx_num_entries * LDC_PACKET_SIZE))
			new = 0;
		lp->rx_head = new;

		err = __set_rx_head(lp, new);
		if (err < 0) {
			(void) LDC_ABORT(lp);
			break;
		}
		if (lp->hs_state == LDC_HS_COMPLETE)
			goto handshake_complete;
	}

out:
	spin_unlock_irqrestore(&lp->lock, flags);

	send_events(lp, event_mask);

	return IRQ_HANDLED;
}