#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u16 ;
struct isowbuf_t {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  isowbuf_putbits (struct isowbuf_t*,int,int) ; 
 int* stufftab ; 

__attribute__((used)) static inline int hdlc_bitstuff_byte(struct isowbuf_t *iwb, unsigned char cin,
				     int ones)
{
	u16 stuff;
	int shiftinc, newones;

	/* get stuffing information for input byte
	 * value: bit  9.. 0 = result bits
	 *        bit 12..10 = number of trailing '1' bits in result
	 *        bit 14..13 = number of bits added by stuffing
	 */
	stuff = stufftab[256 * ones + cin];
	shiftinc = (stuff >> 13) & 3;
	newones = (stuff >> 10) & 7;
	stuff &= 0x3ff;

	/* append stuffed byte to output stream */
	isowbuf_putbits(iwb, stuff, 8 + shiftinc);
	return newones;
}