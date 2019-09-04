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
struct psb_intel_sdvo {int ddc_bus; } ;

/* Variables and functions */

__attribute__((used)) static void
psb_intel_sdvo_guess_ddc_bus(struct psb_intel_sdvo *sdvo)
{
	/* FIXME: At the moment, ddc_bus = 2 is the only thing that works.
	 * We need to figure out if this is true for all available poulsbo
	 * hardware, or if we need to fiddle with the guessing code above.
	 * The problem might go away if we can parse sdvo mappings from bios */
	sdvo->ddc_bus = 2;

#if 0
	uint16_t mask = 0;
	unsigned int num_bits;

	/* Make a mask of outputs less than or equal to our own priority in the
	 * list.
	 */
	switch (sdvo->controlled_output) {
	case SDVO_OUTPUT_LVDS1:
		mask |= SDVO_OUTPUT_LVDS1;
	case SDVO_OUTPUT_LVDS0:
		mask |= SDVO_OUTPUT_LVDS0;
	case SDVO_OUTPUT_TMDS1:
		mask |= SDVO_OUTPUT_TMDS1;
	case SDVO_OUTPUT_TMDS0:
		mask |= SDVO_OUTPUT_TMDS0;
	case SDVO_OUTPUT_RGB1:
		mask |= SDVO_OUTPUT_RGB1;
	case SDVO_OUTPUT_RGB0:
		mask |= SDVO_OUTPUT_RGB0;
		break;
	}

	/* Count bits to find what number we are in the priority list. */
	mask &= sdvo->caps.output_flags;
	num_bits = hweight16(mask);
	/* If more than 3 outputs, default to DDC bus 3 for now. */
	if (num_bits > 3)
		num_bits = 3;

	/* Corresponds to SDVO_CONTROL_BUS_DDCx */
	sdvo->ddc_bus = 1 << num_bits;
#endif
}