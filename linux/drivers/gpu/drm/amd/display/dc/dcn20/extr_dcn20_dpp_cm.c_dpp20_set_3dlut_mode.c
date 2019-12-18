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
struct dpp {int dummy; } ;
struct dcn20_dpp {int dummy; } ;
typedef  enum dc_lut_mode { ____Placeholder_dc_lut_mode } dc_lut_mode ;

/* Variables and functions */
 int /*<<< orphan*/  CM_3DLUT_MODE ; 
 int /*<<< orphan*/  CM_3DLUT_SIZE ; 
 int LUT_BYPASS ; 
 int LUT_RAM_A ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 struct dcn20_dpp* TO_DCN20_DPP (struct dpp*) ; 

__attribute__((used)) static void dpp20_set_3dlut_mode(
		struct dpp *dpp_base,
		enum dc_lut_mode mode,
		bool is_color_channel_12bits,
		bool is_lut_size17x17x17)
{
	uint32_t lut_mode;
	struct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	if (mode == LUT_BYPASS)
		lut_mode = 0;
	else if (mode == LUT_RAM_A)
		lut_mode = 1;
	else
		lut_mode = 2;

	REG_UPDATE_2(CM_3DLUT_MODE,
			CM_3DLUT_MODE, lut_mode,
			CM_3DLUT_SIZE, is_lut_size17x17x17 == true ? 0 : 1);
}