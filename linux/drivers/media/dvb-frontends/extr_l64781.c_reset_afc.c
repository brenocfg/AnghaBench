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
struct l64781_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  l64781_writereg (struct l64781_state*,int,int) ; 

__attribute__((used)) static void reset_afc (struct l64781_state* state)
{
	/* Set AFC stall for the AFC_INIT_FRQ setting, TIM_STALL for
	   timing offset */
	l64781_writereg (state, 0x07, 0x9e); /* stall AFC */
	l64781_writereg (state, 0x08, 0);    /* AFC INIT FREQ */
	l64781_writereg (state, 0x09, 0);
	l64781_writereg (state, 0x0a, 0);
	l64781_writereg (state, 0x07, 0x8e);
	l64781_writereg (state, 0x0e, 0);    /* AGC gain to zero in beginning */
	l64781_writereg (state, 0x11, 0x80); /* stall TIM */
	l64781_writereg (state, 0x10, 0);    /* TIM_OFFSET_LSB */
	l64781_writereg (state, 0x12, 0);
	l64781_writereg (state, 0x13, 0);
	l64781_writereg (state, 0x11, 0x00);
}