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
struct dpp {int dummy; } ;
struct dcn10_dpp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_IGAM_CONTROL ; 
 int /*<<< orphan*/  CM_IGAM_INPUT_FORMAT ; 
 int /*<<< orphan*/  CM_IGAM_LUT_MODE ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dcn10_dpp* TO_DCN10_DPP (struct dpp*) ; 

__attribute__((used)) static void dpp1_set_degamma_format_float(
		struct dpp *dpp_base,
		bool is_float)
{
	struct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	if (is_float) {
		REG_UPDATE(CM_IGAM_CONTROL, CM_IGAM_INPUT_FORMAT, 3);
		REG_UPDATE(CM_IGAM_CONTROL, CM_IGAM_LUT_MODE, 1);
	} else {
		REG_UPDATE(CM_IGAM_CONTROL, CM_IGAM_INPUT_FORMAT, 2);
		REG_UPDATE(CM_IGAM_CONTROL, CM_IGAM_LUT_MODE, 0);
	}
}