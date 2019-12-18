#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  len; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_2__ stats; } ;
struct TYPE_6__ {int numbits; int bitbuf; int tx_state; int numflags; int* buffer; int* bp; int len; int bitstream; int /*<<< orphan*/  in_hdlc_tx; int /*<<< orphan*/  hbuf; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_tail; } ;
struct hdlcdrv_state {scalar_t__ magic; TYPE_3__ hdlctx; struct sk_buff* skb; TYPE_1__ ch_params; } ;

/* Variables and functions */
 scalar_t__ HDLCDRV_MAGIC ; 
 int HDLCDRV_MAXFLEN ; 
 int /*<<< orphan*/  append_crc_ccitt (int*,int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 scalar_t__ hdlcdrv_hbuf_full (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hdlcdrv_hbuf_put (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data_offset (struct sk_buff*,int,int*,int) ; 
 int tenms_to_2flags (struct hdlcdrv_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void hdlcdrv_transmitter(struct net_device *dev, struct hdlcdrv_state *s)
{
	unsigned int mask1, mask2, mask3;
	int i;
	struct sk_buff *skb;
	int pkt_len;

	if (!s || s->magic != HDLCDRV_MAGIC) 
		return;
	if (test_and_set_bit(0, &s->hdlctx.in_hdlc_tx))
		return;
	for (;;) {
		if (s->hdlctx.numbits >= 16) {
			if (hdlcdrv_hbuf_full(&s->hdlctx.hbuf)) {
				clear_bit(0, &s->hdlctx.in_hdlc_tx);
				return;
			}
			hdlcdrv_hbuf_put(&s->hdlctx.hbuf, s->hdlctx.bitbuf);
			s->hdlctx.bitbuf >>= 16;
			s->hdlctx.numbits -= 16;
		}
		switch (s->hdlctx.tx_state) {
		default:
			clear_bit(0, &s->hdlctx.in_hdlc_tx);
			return;
		case 0:
		case 1:
			if (s->hdlctx.numflags) {
				s->hdlctx.numflags--;
				s->hdlctx.bitbuf |= 
					0x7e7e << s->hdlctx.numbits;
				s->hdlctx.numbits += 16;
				break;
			}
			if (s->hdlctx.tx_state == 1) {
				clear_bit(0, &s->hdlctx.in_hdlc_tx);
				return;
			}
			if (!(skb = s->skb)) {
				int flgs = tenms_to_2flags(s, s->ch_params.tx_tail);
				if (flgs < 2)
					flgs = 2;
				s->hdlctx.tx_state = 1;
				s->hdlctx.numflags = flgs;
				break;
			}
			s->skb = NULL;
			netif_wake_queue(dev);
			pkt_len = skb->len-1; /* strip KISS byte */
			if (pkt_len >= HDLCDRV_MAXFLEN || pkt_len < 2) {
				s->hdlctx.tx_state = 0;
				s->hdlctx.numflags = 1;
				dev_kfree_skb_irq(skb);
				break;
			}
			skb_copy_from_linear_data_offset(skb, 1,
							 s->hdlctx.buffer,
							 pkt_len);
			dev_kfree_skb_irq(skb);
			s->hdlctx.bp = s->hdlctx.buffer;
			append_crc_ccitt(s->hdlctx.buffer, pkt_len);
			s->hdlctx.len = pkt_len+2; /* the appended CRC */
			s->hdlctx.tx_state = 2;
			s->hdlctx.bitstream = 0;
			dev->stats.tx_packets++;
			break;
		case 2:
			if (!s->hdlctx.len) {
				s->hdlctx.tx_state = 0;
				s->hdlctx.numflags = 1;
				break;
			}
			s->hdlctx.len--;
			s->hdlctx.bitbuf |= *s->hdlctx.bp <<
				s->hdlctx.numbits;
			s->hdlctx.bitstream >>= 8;
			s->hdlctx.bitstream |= (*s->hdlctx.bp++) << 16;
			mask1 = 0x1f000;
			mask2 = 0x10000;
			mask3 = 0xffffffff >> (31-s->hdlctx.numbits);
			s->hdlctx.numbits += 8;
			for(i = 0; i < 8; i++, mask1 <<= 1, mask2 <<= 1, 
			    mask3 = (mask3 << 1) | 1) {
				if ((s->hdlctx.bitstream & mask1) != mask1) 
					continue;
				s->hdlctx.bitstream &= ~mask2;
				s->hdlctx.bitbuf = 
					(s->hdlctx.bitbuf & mask3) |
						((s->hdlctx.bitbuf & 
						 (~mask3)) << 1);
				s->hdlctx.numbits++;
				mask3 = (mask3 << 1) | 1;
			}
			break;
		}
	}
}