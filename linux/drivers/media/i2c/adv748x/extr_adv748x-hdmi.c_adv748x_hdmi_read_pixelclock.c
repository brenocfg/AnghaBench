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
struct adv748x_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV748X_HDMI_TMDS_1 ; 
 int /*<<< orphan*/  ADV748X_HDMI_TMDS_2 ; 
 int ENODATA ; 
 int hdmi_read (struct adv748x_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adv748x_hdmi_read_pixelclock(struct adv748x_state *state)
{
	int a, b;

	a = hdmi_read(state, ADV748X_HDMI_TMDS_1);
	b = hdmi_read(state, ADV748X_HDMI_TMDS_2);
	if (a < 0 || b < 0)
		return -ENODATA;

	/*
	 * The high 9 bits store TMDS frequency measurement in MHz
	 * The low 7 bits of TMDS_2 store the 7-bit TMDS fractional frequency
	 * measurement in 1/128 MHz
	 */
	return ((a << 1) | (b >> 7)) * 1000000 + (b & 0x7f) * 1000000 / 128;
}