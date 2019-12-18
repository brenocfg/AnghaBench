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
struct TYPE_2__ {struct bas_bc_state* bas; } ;
struct bc_state {int inputstate; TYPE_1__ hw; } ;
struct bas_bc_state {unsigned int seqlen; unsigned int inbyte; unsigned int inbits; int /*<<< orphan*/  aborts; int /*<<< orphan*/  stolen0s; int /*<<< orphan*/  shared0s; } ;

/* Variables and functions */
 int INS_flag_hunt ; 
 int INS_have_data ; 
 unsigned char PPP_FLAG ; 
 unsigned char* bitcounts ; 
 int /*<<< orphan*/  hdlc_done (struct bc_state*) ; 
 int /*<<< orphan*/  hdlc_flush (struct bc_state*) ; 
 int /*<<< orphan*/  hdlc_frag (struct bc_state*,unsigned int) ; 
 int /*<<< orphan*/  hdlc_putbyte (unsigned int,struct bc_state*) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void hdlc_unpack(unsigned char *src, unsigned count,
			       struct bc_state *bcs)
{
	struct bas_bc_state *ubc = bcs->hw.bas;
	int inputstate;
	unsigned seqlen, inbyte, inbits;

	/* load previous state:
	 * inputstate = set of flag bits:
	 * - INS_flag_hunt: no complete opening flag received since connection
	 *                  setup or last abort
	 * - INS_have_data: at least one complete data byte received since last
	 *                  flag
	 * seqlen = number of consecutive '1' bits in last 7 input stream bits
	 *          (0..7)
	 * inbyte = accumulated partial data byte (if !INS_flag_hunt)
	 * inbits = number of valid bits in inbyte, starting at LSB (0..6)
	 */
	inputstate = bcs->inputstate;
	seqlen = ubc->seqlen;
	inbyte = ubc->inbyte;
	inbits = ubc->inbits;

	/* bit unstuffing a byte a time
	 * Take your time to understand this; it's straightforward but tedious.
	 * The "bitcounts" lookup table is used to speed up the counting of
	 * leading and trailing '1' bits.
	 */
	while (count--) {
		unsigned char c = *src++;
		unsigned char tabentry = bitcounts[c];
		unsigned lead1 = tabentry & 0x0f;
		unsigned trail1 = (tabentry >> 4) & 0x0f;

		seqlen += lead1;

		if (unlikely(inputstate & INS_flag_hunt)) {
			if (c == PPP_FLAG) {
				/* flag-in-one */
				inputstate &= ~(INS_flag_hunt | INS_have_data);
				inbyte = 0;
				inbits = 0;
			} else if (seqlen == 6 && trail1 != 7) {
				/* flag completed & not followed by abort */
				inputstate &= ~(INS_flag_hunt | INS_have_data);
				inbyte = c >> (lead1 + 1);
				inbits = 7 - lead1;
				if (trail1 >= 8) {
					/* interior stuffing:
					 * omitting the MSB handles most cases,
					 * correct the incorrectly handled
					 * cases individually */
					inbits--;
					switch (c) {
					case 0xbe:
						inbyte = 0x3f;
						break;
					}
				}
			}
			/* else: continue flag-hunting */
		} else if (likely(seqlen < 5 && trail1 < 7)) {
			/* streamlined case: 8 data bits, no stuffing */
			inbyte |= c << inbits;
			hdlc_putbyte(inbyte & 0xff, bcs);
			inputstate |= INS_have_data;
			inbyte >>= 8;
			/* inbits unchanged */
		} else if (likely(seqlen == 6 && inbits == 7 - lead1 &&
				  trail1 + 1 == inbits &&
				  !(inputstate & INS_have_data))) {
			/* streamlined case: flag idle - state unchanged */
		} else if (unlikely(seqlen > 6)) {
			/* abort sequence */
			ubc->aborts++;
			hdlc_flush(bcs);
			inputstate |= INS_flag_hunt;
		} else if (seqlen == 6) {
			/* closing flag, including (6 - lead1) '1's
			 * and one '0' from inbits */
			if (inbits > 7 - lead1) {
				hdlc_frag(bcs, inbits + lead1 - 7);
				inputstate &= ~INS_have_data;
			} else {
				if (inbits < 7 - lead1)
					ubc->stolen0s++;
				if (inputstate & INS_have_data) {
					hdlc_done(bcs);
					inputstate &= ~INS_have_data;
				}
			}

			if (c == PPP_FLAG) {
				/* complete flag, LSB overlaps preceding flag */
				ubc->shared0s++;
				inbits = 0;
				inbyte = 0;
			} else if (trail1 != 7) {
				/* remaining bits */
				inbyte = c >> (lead1 + 1);
				inbits = 7 - lead1;
				if (trail1 >= 8) {
					/* interior stuffing:
					 * omitting the MSB handles most cases,
					 * correct the incorrectly handled
					 * cases individually */
					inbits--;
					switch (c) {
					case 0xbe:
						inbyte = 0x3f;
						break;
					}
				}
			} else {
				/* abort sequence follows,
				 * skb already empty anyway */
				ubc->aborts++;
				inputstate |= INS_flag_hunt;
			}
		} else { /* (seqlen < 6) && (seqlen == 5 || trail1 >= 7) */

			if (c == PPP_FLAG) {
				/* complete flag */
				if (seqlen == 5)
					ubc->stolen0s++;
				if (inbits) {
					hdlc_frag(bcs, inbits);
					inbits = 0;
					inbyte = 0;
				} else if (inputstate & INS_have_data)
					hdlc_done(bcs);
				inputstate &= ~INS_have_data;
			} else if (trail1 == 7) {
				/* abort sequence */
				ubc->aborts++;
				hdlc_flush(bcs);
				inputstate |= INS_flag_hunt;
			} else {
				/* stuffed data */
				if (trail1 < 7) { /* => seqlen == 5 */
					/* stuff bit at position lead1,
					 * no interior stuffing */
					unsigned char mask = (1 << lead1) - 1;
					c = (c & mask) | ((c & ~mask) >> 1);
					inbyte |= c << inbits;
					inbits += 7;
				} else if (seqlen < 5) { /* trail1 >= 8 */
					/* interior stuffing:
					 * omitting the MSB handles most cases,
					 * correct the incorrectly handled
					 * cases individually */
					switch (c) {
					case 0xbe:
						c = 0x7e;
						break;
					}
					inbyte |= c << inbits;
					inbits += 7;
				} else { /* seqlen == 5 && trail1 >= 8 */

					/* stuff bit at lead1 *and* interior
					 * stuffing -- unstuff individually */
					switch (c) {
					case 0x7d:
						c = 0x3f;
						break;
					case 0xbe:
						c = 0x3f;
						break;
					case 0x3e:
						c = 0x1f;
						break;
					case 0x7c:
						c = 0x3e;
						break;
					}
					inbyte |= c << inbits;
					inbits += 6;
				}
				if (inbits >= 8) {
					inbits -= 8;
					hdlc_putbyte(inbyte & 0xff, bcs);
					inputstate |= INS_have_data;
					inbyte >>= 8;
				}
			}
		}
		seqlen = trail1 & 7;
	}

	/* save new state */
	bcs->inputstate = inputstate;
	ubc->seqlen = seqlen;
	ubc->inbyte = inbyte;
	ubc->inbits = inbits;
}