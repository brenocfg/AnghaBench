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
typedef  scalar_t__ u8 ;
struct cx24113_state {scalar_t__ tuner_gain_thres; scalar_t__ gain_level; } ;
typedef  scalar_t__ s16 ;

/* Variables and functions */
 int RFVGA_0 ; 
 int RFVGA_2 ; 
 int VGA_2 ; 
 int VGA_6 ; 
 int VGA_7 ; 
 int cx24113_readreg (struct cx24113_state*,int) ; 
 int /*<<< orphan*/  cx24113_writereg (struct cx24113_state*,int,scalar_t__) ; 
 int /*<<< orphan*/  dprintk (char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int cx24113_set_gain_settings(struct cx24113_state *state,
		s16 power_estimation)
{
	u8 ampout = cx24113_readreg(state, 0x1d) & 0xf0,
	   vga    = cx24113_readreg(state, 0x1f) & 0x3f,
	   rfvga  = cx24113_readreg(state, 0x20) & 0xf3;
	u8 gain_level = power_estimation >= state->tuner_gain_thres;

	dprintk("power estimation: %d, thres: %d, gain_level: %d/%d\n",
			power_estimation, state->tuner_gain_thres,
			state->gain_level, gain_level);

	if (gain_level == state->gain_level)
		return 0; /* nothing to be done */

	ampout |= 0xf;

	if (gain_level) {
		rfvga |= RFVGA_0 << 2;
		vga   |= (VGA_7 << 3) | VGA_7;
	} else {
		rfvga |= RFVGA_2 << 2;
		vga  |= (VGA_6 << 3) | VGA_2;
	}
	state->gain_level = gain_level;

	cx24113_writereg(state, 0x1d, ampout);
	cx24113_writereg(state, 0x1f, vga);
	cx24113_writereg(state, 0x20, rfvga);

	return 1; /* did something */
}