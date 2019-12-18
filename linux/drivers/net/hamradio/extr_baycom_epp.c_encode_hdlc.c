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
struct sk_buff {int len; unsigned char* data; } ;
struct TYPE_4__ {int bufcnt; unsigned char* buf; unsigned char* bufptr; } ;
struct baycom_state {TYPE_3__* dev; TYPE_1__ hdlctx; struct sk_buff* skb; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_packets; } ;
struct TYPE_6__ {TYPE_2__ stats; } ;

/* Variables and functions */
 unsigned int calc_crc_ccitt (unsigned char*,int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void encode_hdlc(struct baycom_state *bc)
{
	struct sk_buff *skb;
	unsigned char *wp, *bp;
	int pkt_len;
        unsigned bitstream, notbitstream, bitbuf, numbit, crc;
	unsigned char crcarr[2];
	int j;
	
	if (bc->hdlctx.bufcnt > 0)
		return;
	skb = bc->skb;
	if (!skb)
		return;
	bc->skb = NULL;
	pkt_len = skb->len-1; /* strip KISS byte */
	wp = bc->hdlctx.buf;
	bp = skb->data+1;
	crc = calc_crc_ccitt(bp, pkt_len);
	crcarr[0] = crc;
	crcarr[1] = crc >> 8;
	*wp++ = 0x7e;
	bitstream = bitbuf = numbit = 0;
	while (pkt_len > -2) {
		bitstream >>= 8;
		bitstream |= ((unsigned int)*bp) << 8;
		bitbuf |= ((unsigned int)*bp) << numbit;
		notbitstream = ~bitstream;
		bp++;
		pkt_len--;
		if (!pkt_len)
			bp = crcarr;
		for (j = 0; j < 8; j++)
			if (unlikely(!(notbitstream & (0x1f0 << j)))) {
				bitstream &= ~(0x100 << j);
 				bitbuf = (bitbuf & (((2 << j) << numbit) - 1)) |
					((bitbuf & ~(((2 << j) << numbit) - 1)) << 1);
				numbit++;
				notbitstream = ~bitstream;
			}
		numbit += 8;
		while (numbit >= 8) {
			*wp++ = bitbuf;
			bitbuf >>= 8;
			numbit -= 8;
		}
	}
	bitbuf |= 0x7e7e << numbit;
	numbit += 16;
	while (numbit >= 8) {
		*wp++ = bitbuf;
		bitbuf >>= 8;
		numbit -= 8;
	}
	bc->hdlctx.bufptr = bc->hdlctx.buf;
	bc->hdlctx.bufcnt = wp - bc->hdlctx.buf;
	dev_kfree_skb(skb);
	bc->dev->stats.tx_packets++;
}