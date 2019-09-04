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
struct bttv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_bits (int,unsigned int) ; 

__attribute__((used)) static void kodicom4400r_write(struct bttv *btv,
			       unsigned char xaddr,
			       unsigned char yaddr,
			       unsigned char data) {
	unsigned int udata;

	udata = (data << 7) | ((yaddr&3) << 4) | (xaddr&0xf);
	gpio_bits(0x1ff, udata);		/* write ADDR and DAT */
	gpio_bits(0x1ff, udata | (1 << 8));	/* strobe high */
	gpio_bits(0x1ff, udata);		/* strobe low */
}