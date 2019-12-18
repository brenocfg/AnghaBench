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
typedef  int u16 ;

/* Variables and functions */
 unsigned long UWIRE_CLK_INVERTED ; 
 int UWIRE_SR1 ; 
 int UWIRE_SR2 ; 
 int uwire_read_reg (int) ; 
 int /*<<< orphan*/  uwire_write_reg (int,int) ; 

__attribute__((used)) static inline void omap_uwire_configure_mode(u8 cs, unsigned long flags)
{
	u16	w, val = 0;
	int	shift, reg;

	if (flags & UWIRE_CLK_INVERTED)
		val ^= 0x03;
	val = flags & 0x3f;
	if (cs & 1)
		shift = 6;
	else
		shift = 0;
	if (cs <= 1)
		reg = UWIRE_SR1;
	else
		reg = UWIRE_SR2;

	w = uwire_read_reg(reg);
	w &= ~(0x3f << shift);
	w |= val << shift;
	uwire_write_reg(reg, w);
}