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
typedef  enum dc_lut_mode { ____Placeholder_dc_lut_mode } dc_lut_mode ;

/* Variables and functions */
 int /*<<< orphan*/  CM_3DLUT_30BIT_EN ; 
 int /*<<< orphan*/  CM_3DLUT_RAM_SEL ; 
 int /*<<< orphan*/  CM_3DLUT_READ_WRITE_CONTROL ; 
 int LUT_RAM_A ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 struct dcn20_dpp* TO_DCN20_DPP (struct dpp*) ; 

__attribute__((used)) static void dpp20_select_3dlut_ram(
		struct dpp *dpp_base,
		enum dc_lut_mode mode,
		bool is_color_channel_12bits)
{
	struct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	REG_UPDATE_2(CM_3DLUT_READ_WRITE_CONTROL,
			CM_3DLUT_RAM_SEL, mode == LUT_RAM_A ? 0 : 1,
			CM_3DLUT_30BIT_EN,
			is_color_channel_12bits == true ? 0:1);
}