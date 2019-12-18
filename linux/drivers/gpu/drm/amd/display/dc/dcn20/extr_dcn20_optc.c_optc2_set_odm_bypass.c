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
typedef  int /*<<< orphan*/  uint32_t ;
struct timing_generator {int /*<<< orphan*/  inst; } ;
struct optc {int opp_count; } ;
struct dc_crtc_timing {int dummy; } ;

/* Variables and functions */
 struct optc* DCN10TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  OPTC_DATA_SOURCE_SELECT ; 
 int /*<<< orphan*/  OPTC_MEMORY_CONFIG ; 
 int /*<<< orphan*/  OPTC_MEM_SEL ; 
 int /*<<< orphan*/  OPTC_NUM_OF_INPUT_SEGMENT ; 
 int /*<<< orphan*/  OPTC_SEG0_SRC_SEL ; 
 int /*<<< orphan*/  OPTC_SEG1_SRC_SEL ; 
 int /*<<< orphan*/  OTG_H_TIMING_CNTL ; 
 int /*<<< orphan*/  OTG_H_TIMING_DIV_BY2 ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optc1_is_two_pixels_per_containter (struct dc_crtc_timing const*) ; 

void optc2_set_odm_bypass(struct timing_generator *optc,
		const struct dc_crtc_timing *dc_crtc_timing)
{
	struct optc *optc1 = DCN10TG_FROM_TG(optc);
	uint32_t h_div_2 = 0;

	REG_SET_3(OPTC_DATA_SOURCE_SELECT, 0,
			OPTC_NUM_OF_INPUT_SEGMENT, 0,
			OPTC_SEG0_SRC_SEL, optc->inst,
			OPTC_SEG1_SRC_SEL, 0xf);
	REG_WRITE(OTG_H_TIMING_CNTL, 0);

	h_div_2 = optc1_is_two_pixels_per_containter(dc_crtc_timing);
	REG_UPDATE(OTG_H_TIMING_CNTL,
			OTG_H_TIMING_DIV_BY2, h_div_2);
	REG_SET(OPTC_MEMORY_CONFIG, 0,
			OPTC_MEM_SEL, 0);
	optc1->opp_count = 1;
}