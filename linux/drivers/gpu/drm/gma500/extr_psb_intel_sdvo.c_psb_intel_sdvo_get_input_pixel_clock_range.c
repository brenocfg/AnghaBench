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
struct psb_intel_sdvo_pixel_clock_range {int min; int max; } ;
struct psb_intel_sdvo {int dummy; } ;
typedef  int /*<<< orphan*/  clocks ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  SDVO_CMD_GET_INPUT_PIXEL_CLOCK_RANGE ; 
 int /*<<< orphan*/  psb_intel_sdvo_get_value (struct psb_intel_sdvo*,int /*<<< orphan*/ ,struct psb_intel_sdvo_pixel_clock_range*,int) ; 

__attribute__((used)) static bool psb_intel_sdvo_get_input_pixel_clock_range(struct psb_intel_sdvo *psb_intel_sdvo,
						   int *clock_min,
						   int *clock_max)
{
	struct psb_intel_sdvo_pixel_clock_range clocks;

	BUILD_BUG_ON(sizeof(clocks) != 4);
	if (!psb_intel_sdvo_get_value(psb_intel_sdvo,
				  SDVO_CMD_GET_INPUT_PIXEL_CLOCK_RANGE,
				  &clocks, sizeof(clocks)))
		return false;

	/* Convert the values from units of 10 kHz to kHz. */
	*clock_min = clocks.min * 10;
	*clock_max = clocks.max * 10;
	return true;
}