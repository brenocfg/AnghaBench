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
typedef  int u16 ;

/* Variables and functions */
 int PS_PHASE_MASK ; 
 int PS_PHASE_TRIP ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

u16 skl_scaler_calc_phase(int sub, int scale, bool chroma_cosited)
{
	int phase = -0x8000;
	u16 trip = 0;

	if (chroma_cosited)
		phase += (sub - 1) * 0x8000 / sub;

	phase += scale / (2 * sub);

	/*
	 * Hardware initial phase limited to [-0.5:1.5].
	 * Since the max hardware scale factor is 3.0, we
	 * should never actually excdeed 1.0 here.
	 */
	WARN_ON(phase < -0x8000 || phase > 0x18000);

	if (phase < 0)
		phase = 0x10000 + phase;
	else
		trip = PS_PHASE_TRIP;

	return ((phase >> 2) & PS_PHASE_MASK) | trip;
}