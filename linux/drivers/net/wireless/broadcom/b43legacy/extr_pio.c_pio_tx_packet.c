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
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ len; } ;
struct b43legacy_txhdr_fw3 {int dummy; } ;
struct b43legacy_pioqueue {scalar_t__ tx_devq_size; scalar_t__ tx_devq_packets; scalar_t__ tx_devq_used; int /*<<< orphan*/  txrunning; TYPE_1__* dev; } ;
struct b43legacy_pio_txpacket {int /*<<< orphan*/  list; struct sk_buff* skb; struct b43legacy_pioqueue* queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  wl; } ;

/* Variables and functions */
 scalar_t__ B43legacy_PIO_MAXTXDEVQPACKETS ; 
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 
 int EBUSY ; 
 int ENOKEY ; 
 int /*<<< orphan*/  b43legacywarn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_txpacket (struct b43legacy_pio_txpacket*,int) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pio_tx_write_fragment (struct b43legacy_pioqueue*,struct sk_buff*,struct b43legacy_pio_txpacket*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int pio_tx_packet(struct b43legacy_pio_txpacket *packet)
{
	struct b43legacy_pioqueue *queue = packet->queue;
	struct sk_buff *skb = packet->skb;
	u16 octets;
	int err;

	octets = (u16)skb->len + sizeof(struct b43legacy_txhdr_fw3);
	if (queue->tx_devq_size < octets) {
		b43legacywarn(queue->dev->wl, "PIO queue too small. "
			"Dropping packet.\n");
		/* Drop it silently (return success) */
		free_txpacket(packet, 1);
		return 0;
	}
	B43legacy_WARN_ON(queue->tx_devq_packets >
			  B43legacy_PIO_MAXTXDEVQPACKETS);
	B43legacy_WARN_ON(queue->tx_devq_used > queue->tx_devq_size);
	/* Check if there is sufficient free space on the device
	 * TX queue. If not, return and let the TX tasklet
	 * retry later.
	 */
	if (queue->tx_devq_packets == B43legacy_PIO_MAXTXDEVQPACKETS)
		return -EBUSY;
	if (queue->tx_devq_used + octets > queue->tx_devq_size)
		return -EBUSY;
	/* Now poke the device. */
	err = pio_tx_write_fragment(queue, skb, packet,
			      sizeof(struct b43legacy_txhdr_fw3));
	if (unlikely(err == -ENOKEY)) {
		/* Drop this packet, as we don't have the encryption key
		 * anymore and must not transmit it unencrypted. */
		free_txpacket(packet, 1);
		return 0;
	}

	/* Account for the packet size.
	 * (We must not overflow the device TX queue)
	 */
	queue->tx_devq_packets++;
	queue->tx_devq_used += octets;

	/* Transmission started, everything ok, move the
	 * packet to the txrunning list.
	 */
	list_move_tail(&packet->list, &queue->txrunning);

	return 0;
}