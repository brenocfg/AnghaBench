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

/* Variables and functions */

__attribute__((used)) static int imgu_css_osys_out_stripe_width(int stripe_width_inp, int fir_phases,
					  int phase_init, int phase_step,
					  int fir_taps, int pad_left,
					  int pad_right, int column_offset)
{
	int stripe_width_out = (pad_left + stripe_width_inp +
				pad_right - column_offset) * phase_step;

	stripe_width_out = (stripe_width_out + phase_init) / fir_phases;

	return stripe_width_out - (fir_taps - 1);
}