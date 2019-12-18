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
struct ni_gpct {int /*<<< orphan*/  counter_index; } ;

/* Variables and functions */
 int CR_CHAN (unsigned int) ; 
 unsigned int CR_INVERT ; 
 unsigned int GI_GATE2_MODE ; 
 unsigned int GI_GATE2_POL_INVERT ; 
 unsigned int GI_GATING_DISABLED ; 
 int /*<<< orphan*/  NITIO_GATE2_REG (int /*<<< orphan*/ ) ; 
 int NI_GPCT_DISABLED_GATE_SELECT ; 
 int /*<<< orphan*/  ni_tio_set_bits (struct ni_gpct*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static inline void ni_tio_set_gate2_mode(struct ni_gpct *counter,
					 unsigned int src)
{
	/*
	 * The GI_GATE2_MODE bit was previously set in the code that also sets
	 * the gate2 source.
	 * We'll set mode bits _after_ source bits now, and thus, this function
	 * will effectively enable the second gate after all bits are set.
	 */
	unsigned int mode_bits = GI_GATE2_MODE;

	if (CR_CHAN(src) & NI_GPCT_DISABLED_GATE_SELECT)
		/*
		 * Allowing bitwise comparison here to allow non-zero raw
		 * register value to be used for channel when disabling.
		 */
		mode_bits = GI_GATING_DISABLED;
	if (src & CR_INVERT)
		mode_bits |= GI_GATE2_POL_INVERT;

	ni_tio_set_bits(counter, NITIO_GATE2_REG(counter->counter_index),
			GI_GATE2_POL_INVERT | GI_GATE2_MODE, mode_bits);
}