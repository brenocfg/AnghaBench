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
struct nvidia_par {int dummy; } ;

/* Variables and functions */
 unsigned char NVReadSeq (struct nvidia_par*,int) ; 
 int /*<<< orphan*/  NVWriteSeq (struct nvidia_par*,int,int) ; 

__attribute__((used)) static void nvidia_screen_off(struct nvidia_par *par, int on)
{
	unsigned char tmp;

	if (on) {
		/*
		 * Turn off screen and disable sequencer.
		 */
		tmp = NVReadSeq(par, 0x01);

		NVWriteSeq(par, 0x00, 0x01);		/* Synchronous Reset */
		NVWriteSeq(par, 0x01, tmp | 0x20);	/* disable the display */
	} else {
		/*
		 * Reenable sequencer, then turn on screen.
		 */

		tmp = NVReadSeq(par, 0x01);

		NVWriteSeq(par, 0x01, tmp & ~0x20);	/* reenable display */
		NVWriteSeq(par, 0x00, 0x03);		/* End Reset */
	}
}