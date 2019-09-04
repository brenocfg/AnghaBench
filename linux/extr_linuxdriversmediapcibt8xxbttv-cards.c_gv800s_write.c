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
struct bttv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_bits (int,int const) ; 

__attribute__((used)) static void gv800s_write(struct bttv *btv,
			 unsigned char xaddr,
			 unsigned char yaddr,
			 unsigned char data) {
	/* On the "master" 878A:
	* GPIO bits 0-9 are used for the analog switch:
	*   00 - 03:	camera selector
	*   04 - 06:	878A (controller) selector
	*   16:		cselect
	*   17:		strobe
	*   18:		data (1->on, 0->off)
	*   19:		reset
	*/
	const u32 ADDRESS = ((xaddr&0xf) | (yaddr&3)<<4);
	const u32 CSELECT = 1<<16;
	const u32 STROBE = 1<<17;
	const u32 DATA = data<<18;

	gpio_bits(0x1007f, ADDRESS | CSELECT);	/* write ADDRESS and CSELECT */
	gpio_bits(0x20000, STROBE);		/* STROBE high */
	gpio_bits(0x40000, DATA);		/* write DATA */
	gpio_bits(0x20000, ~STROBE);		/* STROBE low */
}