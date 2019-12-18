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
 int /*<<< orphan*/  CM_DGAM_CONTROL ; 
 int /*<<< orphan*/  CM_DGAM_LUT_MODE ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dcn10_dpp* TO_DCN10_DPP (struct dpp*) ; 

void dpp1_degamma_ram_select(
		struct dpp *dpp_base,
							bool use_ram_a)
{
	struct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	if (use_ram_a)
		REG_UPDATE(CM_DGAM_CONTROL, CM_DGAM_LUT_MODE, 3);
	else
		REG_UPDATE(CM_DGAM_CONTROL, CM_DGAM_LUT_MODE, 4);

}