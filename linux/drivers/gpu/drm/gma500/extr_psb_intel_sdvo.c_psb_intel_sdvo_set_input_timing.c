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
struct psb_intel_sdvo_dtd {int dummy; } ;
struct psb_intel_sdvo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDVO_CMD_SET_INPUT_TIMINGS_PART1 ; 
 int psb_intel_sdvo_set_timing (struct psb_intel_sdvo*,int /*<<< orphan*/ ,struct psb_intel_sdvo_dtd*) ; 

__attribute__((used)) static bool psb_intel_sdvo_set_input_timing(struct psb_intel_sdvo *psb_intel_sdvo,
					 struct psb_intel_sdvo_dtd *dtd)
{
	return psb_intel_sdvo_set_timing(psb_intel_sdvo,
				     SDVO_CMD_SET_INPUT_TIMINGS_PART1, dtd);
}