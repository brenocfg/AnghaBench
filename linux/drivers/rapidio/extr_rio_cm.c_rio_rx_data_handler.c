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
struct TYPE_2__ {size_t count; size_t head; void** buf; } ;
struct rio_channel {scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  comp; TYPE_1__ rx_ring; int /*<<< orphan*/  id; } ;
struct rio_ch_chan_hdr {int /*<<< orphan*/  dst_ch; } ;
struct cm_dev {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 size_t RIOCM_RX_RING_SIZE ; 
 scalar_t__ RIO_CM_CONNECTED ; 
 int /*<<< orphan*/  RX_DATA ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  riocm_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 struct rio_channel* riocm_get_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  riocm_put_channel (struct rio_channel*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rio_rx_data_handler(struct cm_dev *cm, void *buf)
{
	struct rio_ch_chan_hdr *hdr;
	struct rio_channel *ch;

	hdr = buf;

	riocm_debug(RX_DATA, "for ch=%d", ntohs(hdr->dst_ch));

	ch = riocm_get_channel(ntohs(hdr->dst_ch));
	if (!ch) {
		/* Discard data message for non-existing channel */
		kfree(buf);
		return -ENODEV;
	}

	/* Place pointer to the buffer into channel's RX queue */
	spin_lock(&ch->lock);

	if (ch->state != RIO_CM_CONNECTED) {
		/* Channel is not ready to receive data, discard a packet */
		riocm_debug(RX_DATA, "ch=%d is in wrong state=%d",
			    ch->id, ch->state);
		spin_unlock(&ch->lock);
		kfree(buf);
		riocm_put_channel(ch);
		return -EIO;
	}

	if (ch->rx_ring.count == RIOCM_RX_RING_SIZE) {
		/* If RX ring is full, discard a packet */
		riocm_debug(RX_DATA, "ch=%d is full", ch->id);
		spin_unlock(&ch->lock);
		kfree(buf);
		riocm_put_channel(ch);
		return -ENOMEM;
	}

	ch->rx_ring.buf[ch->rx_ring.head] = buf;
	ch->rx_ring.head++;
	ch->rx_ring.count++;
	ch->rx_ring.head %= RIOCM_RX_RING_SIZE;

	complete(&ch->comp);

	spin_unlock(&ch->lock);
	riocm_put_channel(ch);

	return 0;
}