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
typedef  char u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct b43_pio_txqueue {int dummy; } ;
struct b43_pio_txpacket {TYPE_1__* skb; struct b43_pio_txqueue* queue; } ;
struct TYPE_2__ {char* data; unsigned int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_PIO_TXCTL ; 
 int /*<<< orphan*/  B43_PIO_TXCTL_EOF ; 
 int /*<<< orphan*/  B43_PIO_TXCTL_FREADY ; 
 int /*<<< orphan*/  b43_piotx_read16 (struct b43_pio_txqueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_piotx_write16 (struct b43_pio_txqueue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tx_write_2byte_queue (struct b43_pio_txqueue*,int /*<<< orphan*/ ,char const*,unsigned int) ; 

__attribute__((used)) static void pio_tx_frame_2byte_queue(struct b43_pio_txpacket *pack,
				     const u8 *hdr, unsigned int hdrlen)
{
	struct b43_pio_txqueue *q = pack->queue;
	const char *frame = pack->skb->data;
	unsigned int frame_len = pack->skb->len;
	u16 ctl;

	ctl = b43_piotx_read16(q, B43_PIO_TXCTL);
	ctl |= B43_PIO_TXCTL_FREADY;
	ctl &= ~B43_PIO_TXCTL_EOF;

	/* Transfer the header data. */
	ctl = tx_write_2byte_queue(q, ctl, hdr, hdrlen);
	/* Transfer the frame data. */
	ctl = tx_write_2byte_queue(q, ctl, frame, frame_len);

	ctl |= B43_PIO_TXCTL_EOF;
	b43_piotx_write16(q, B43_PIO_TXCTL, ctl);
}