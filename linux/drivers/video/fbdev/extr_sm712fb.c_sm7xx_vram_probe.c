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
typedef  int u_long ;
typedef  int u8 ;
struct smtcfb_info {int chip_id; } ;

/* Variables and functions */
 int inb_p (int) ; 
 int /*<<< orphan*/  outb_p (int,int) ; 

__attribute__((used)) static u_long sm7xx_vram_probe(struct smtcfb_info *sfb)
{
	u8 vram;

	switch (sfb->chip_id) {
	case 0x710:
	case 0x712:
		/*
		 * Assume SM712 graphics chip has 4MB VRAM.
		 *
		 * FIXME: SM712 can have 2MB VRAM, which is used on earlier
		 * laptops, such as IBM Thinkpad 240X. This driver would
		 * probably crash on those machines. If anyone gets one of
		 * those and is willing to help, run "git blame" and send me
		 * an E-mail.
		 */
		return 0x00400000;
	case 0x720:
		outb_p(0x76, 0x3c4);
		vram = inb_p(0x3c5) >> 6;

		if (vram == 0x00)
			return 0x00800000;  /* 8 MB */
		else if (vram == 0x01)
			return 0x01000000;  /* 16 MB */
		else if (vram == 0x02)
			return 0x00400000;  /* illegal, fallback to 4 MB */
		else if (vram == 0x03)
			return 0x00400000;  /* 4 MB */
	}
	return 0;  /* unknown hardware */
}