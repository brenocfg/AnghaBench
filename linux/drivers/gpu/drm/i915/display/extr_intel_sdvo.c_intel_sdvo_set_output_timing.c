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
struct intel_sdvo_dtd {int dummy; } ;
struct intel_sdvo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDVO_CMD_SET_OUTPUT_TIMINGS_PART1 ; 
 int intel_sdvo_set_timing (struct intel_sdvo*,int /*<<< orphan*/ ,struct intel_sdvo_dtd*) ; 

__attribute__((used)) static bool intel_sdvo_set_output_timing(struct intel_sdvo *intel_sdvo,
					 struct intel_sdvo_dtd *dtd)
{
	return intel_sdvo_set_timing(intel_sdvo,
				     SDVO_CMD_SET_OUTPUT_TIMINGS_PART1, dtd);
}