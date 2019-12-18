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
typedef  int uint32_t ;
struct input_pixel_processor {int dummy; } ;
struct dce_ipp {int dummy; } ;
typedef  enum ipp_degamma_mode { ____Placeholder_ipp_degamma_mode } ipp_degamma_mode ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  CURSOR2_DEGAMMA_MODE ; 
 int /*<<< orphan*/  CURSOR_DEGAMMA_MODE ; 
 int /*<<< orphan*/  DEGAMMA_CONTROL ; 
 int /*<<< orphan*/  GRPH_DEGAMMA_MODE ; 
 int IPP_DEGAMMA_MODE_BYPASS ; 
 int IPP_DEGAMMA_MODE_HW_sRGB ; 
 int /*<<< orphan*/  REG_SET_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 struct dce_ipp* TO_DCE_IPP (struct input_pixel_processor*) ; 

__attribute__((used)) static void dce_ipp_set_degamma(
	struct input_pixel_processor *ipp,
	enum ipp_degamma_mode mode)
{
	struct dce_ipp *ipp_dce = TO_DCE_IPP(ipp);
	uint32_t degamma_type = (mode == IPP_DEGAMMA_MODE_HW_sRGB) ? 1 : 0;

	ASSERT(mode == IPP_DEGAMMA_MODE_BYPASS || mode == IPP_DEGAMMA_MODE_HW_sRGB);

	REG_SET_3(DEGAMMA_CONTROL, 0,
		  GRPH_DEGAMMA_MODE, degamma_type,
		  CURSOR_DEGAMMA_MODE, degamma_type,
		  CURSOR2_DEGAMMA_MODE, degamma_type);
}