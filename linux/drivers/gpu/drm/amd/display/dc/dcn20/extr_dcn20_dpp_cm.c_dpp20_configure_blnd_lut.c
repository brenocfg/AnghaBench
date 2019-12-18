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
struct dcn20_dpp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_BLNDGAM_LUT_INDEX ; 
 int /*<<< orphan*/  CM_BLNDGAM_LUT_WRITE_EN_MASK ; 
 int /*<<< orphan*/  CM_BLNDGAM_LUT_WRITE_SEL ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dcn20_dpp* TO_DCN20_DPP (struct dpp*) ; 

__attribute__((used)) static void dpp20_configure_blnd_lut(
		struct dpp *dpp_base,
		bool is_ram_a)
{
	struct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	REG_UPDATE(CM_BLNDGAM_LUT_WRITE_EN_MASK,
			CM_BLNDGAM_LUT_WRITE_EN_MASK, 7);
	REG_UPDATE(CM_BLNDGAM_LUT_WRITE_EN_MASK,
			CM_BLNDGAM_LUT_WRITE_SEL, is_ram_a == true ? 0:1);
	REG_SET(CM_BLNDGAM_LUT_INDEX, 0, CM_BLNDGAM_LUT_INDEX, 0);
}