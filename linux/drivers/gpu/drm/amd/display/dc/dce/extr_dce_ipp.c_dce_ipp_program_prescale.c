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
struct ipp_prescale_params {scalar_t__ mode; int /*<<< orphan*/  bias; int /*<<< orphan*/  scale; } ;
struct input_pixel_processor {int dummy; } ;
struct dce_ipp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRPH_INPUT_GAMMA_MODE ; 
 int /*<<< orphan*/  GRPH_PRESCALE_BIAS_B ; 
 int /*<<< orphan*/  GRPH_PRESCALE_BIAS_G ; 
 int /*<<< orphan*/  GRPH_PRESCALE_BIAS_R ; 
 int /*<<< orphan*/  GRPH_PRESCALE_BYPASS ; 
 int /*<<< orphan*/  GRPH_PRESCALE_SCALE_B ; 
 int /*<<< orphan*/  GRPH_PRESCALE_SCALE_G ; 
 int /*<<< orphan*/  GRPH_PRESCALE_SCALE_R ; 
 int /*<<< orphan*/  INPUT_GAMMA_CONTROL ; 
 scalar_t__ IPP_PRESCALE_MODE_BYPASS ; 
 int /*<<< orphan*/  PRESCALE_GRPH_CONTROL ; 
 int /*<<< orphan*/  PRESCALE_VALUES_GRPH_B ; 
 int /*<<< orphan*/  PRESCALE_VALUES_GRPH_G ; 
 int /*<<< orphan*/  PRESCALE_VALUES_GRPH_R ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dce_ipp* TO_DCE_IPP (struct input_pixel_processor*) ; 

__attribute__((used)) static void dce_ipp_program_prescale(struct input_pixel_processor *ipp,
				     struct ipp_prescale_params *params)
{
	struct dce_ipp *ipp_dce = TO_DCE_IPP(ipp);

	/* set to bypass mode first before change */
	REG_UPDATE(PRESCALE_GRPH_CONTROL,
		   GRPH_PRESCALE_BYPASS, 1);

	REG_SET_2(PRESCALE_VALUES_GRPH_R, 0,
		  GRPH_PRESCALE_SCALE_R, params->scale,
		  GRPH_PRESCALE_BIAS_R, params->bias);

	REG_SET_2(PRESCALE_VALUES_GRPH_G, 0,
		  GRPH_PRESCALE_SCALE_G, params->scale,
		  GRPH_PRESCALE_BIAS_G, params->bias);

	REG_SET_2(PRESCALE_VALUES_GRPH_B, 0,
		  GRPH_PRESCALE_SCALE_B, params->scale,
		  GRPH_PRESCALE_BIAS_B, params->bias);

	if (params->mode != IPP_PRESCALE_MODE_BYPASS) {
		REG_UPDATE(PRESCALE_GRPH_CONTROL,
			   GRPH_PRESCALE_BYPASS, 0);

		/* If prescale is in use, then legacy lut should be bypassed */
		REG_UPDATE(INPUT_GAMMA_CONTROL,
			   GRPH_INPUT_GAMMA_MODE, 1);
	}
}