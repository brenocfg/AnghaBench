#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ ctm; } ;
struct intel_crtc_state {scalar_t__ output_format; scalar_t__ limited_color_range; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICL_CSC_ENABLE ; 
 int /*<<< orphan*/  ICL_OUTPUT_CSC_ENABLE ; 
 scalar_t__ INTEL_OUTPUT_FORMAT_RGB ; 

__attribute__((used)) static u32 icl_csc_mode(const struct intel_crtc_state *crtc_state)
{
	u32 csc_mode = 0;

	if (crtc_state->base.ctm)
		csc_mode |= ICL_CSC_ENABLE;

	if (crtc_state->output_format != INTEL_OUTPUT_FORMAT_RGB ||
	    crtc_state->limited_color_range)
		csc_mode |= ICL_OUTPUT_CSC_ENABLE;

	return csc_mode;
}