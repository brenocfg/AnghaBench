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
typedef  int u32 ;
struct isowbuf_t {int write; int wbits; int* data; } ;

/* Variables and functions */
 int BAS_OUTBUFSIZE ; 

__attribute__((used)) static inline void isowbuf_putbits(struct isowbuf_t *iwb, u32 data, int nbits)
{
	int write = iwb->write;
	data <<= iwb->wbits;
	data |= iwb->data[write];
	nbits += iwb->wbits;
	while (nbits >= 8) {
		iwb->data[write++] = data & 0xff;
		write %= BAS_OUTBUFSIZE;
		data >>= 8;
		nbits -= 8;
	}
	iwb->wbits = nbits;
	iwb->data[write] = data & 0xff;
	iwb->write = write;
}