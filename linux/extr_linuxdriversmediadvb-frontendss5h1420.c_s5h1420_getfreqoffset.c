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
struct s5h1420_state {int fclk; } ;

/* Variables and functions */
 int s5h1420_readreg (struct s5h1420_state*,int) ; 
 int /*<<< orphan*/  s5h1420_writereg (struct s5h1420_state*,int,int) ; 

__attribute__((used)) static int s5h1420_getfreqoffset(struct s5h1420_state* state)
{
	int val;

	s5h1420_writereg(state, 0x06, s5h1420_readreg(state, 0x06) | 0x08);
	val  = s5h1420_readreg(state, 0x0e) << 16;
	val |= s5h1420_readreg(state, 0x0f) << 8;
	val |= s5h1420_readreg(state, 0x10);
	s5h1420_writereg(state, 0x06, s5h1420_readreg(state, 0x06) & 0xf7);

	if (val & 0x800000)
		val |= 0xff000000;

	/* remember freqoffset is in kHz, but the chip wants the offset in Hz, so
	 * divide fclk by 1000000 to get the correct value. */
	val = (((-val) * (state->fclk/1000000)) / (1<<24));

	return val;
}