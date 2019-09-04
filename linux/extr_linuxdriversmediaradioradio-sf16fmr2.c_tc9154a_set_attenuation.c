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
typedef  int u8 ;
typedef  int u32 ;
struct fmr2 {int dummy; } ;

/* Variables and functions */
 int PT_CK ; 
 int PT_DATA ; 
 int PT_ST ; 
 int TC9154A_ATT_MAJ (int) ; 
 int TC9154A_ATT_MIN (int) ; 
 int /*<<< orphan*/  tc9154a_set_pins (struct fmr2*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void tc9154a_set_attenuation(struct fmr2 *fmr2, int att, u32 channel)
{
	int i;
	u32 reg;
	u8 bit;

	reg = TC9154A_ATT_MAJ(att / 10) | TC9154A_ATT_MIN((att % 10) / 2);
	reg |= channel;
	/* write 18-bit shift register, LSB first */
	for (i = 0; i < 18; i++) {
		bit = reg & (1 << i) ? PT_DATA : 0;
		tc9154a_set_pins(fmr2, bit);
		udelay(5);
		tc9154a_set_pins(fmr2, bit | PT_CK);
		udelay(5);
		tc9154a_set_pins(fmr2, bit);
	}

	/* latch register data */
	udelay(5);
	tc9154a_set_pins(fmr2, PT_ST);
	udelay(5);
	tc9154a_set_pins(fmr2, 0);
}