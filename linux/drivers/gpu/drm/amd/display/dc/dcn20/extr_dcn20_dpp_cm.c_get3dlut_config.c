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
 int /*<<< orphan*/  CM_3DLUT_30BIT_EN ; 
 int /*<<< orphan*/  CM_3DLUT_CONFIG_STATUS ; 
 int /*<<< orphan*/  CM_3DLUT_MODE ; 
 int /*<<< orphan*/  CM_3DLUT_READ_WRITE_CONTROL ; 
 int /*<<< orphan*/  CM_3DLUT_SIZE ; 
 int LUT_BYPASS ; 
 int LUT_RAM_A ; 
 int LUT_RAM_B ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  REG_GET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int*) ; 
 struct dcn20_dpp* TO_DCN20_DPP (struct dpp*) ; 

__attribute__((used)) static enum dc_lut_mode get3dlut_config(
			struct dpp *dpp_base,
			bool *is_17x17x17,
			bool *is_12bits_color_channel)
{
	uint32_t i_mode, i_enable_10bits, lut_size;
	enum dc_lut_mode mode;
	struct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	REG_GET_2(CM_3DLUT_READ_WRITE_CONTROL,
			CM_3DLUT_CONFIG_STATUS, &i_mode,
			CM_3DLUT_30BIT_EN, &i_enable_10bits);

	switch (i_mode) {
	case 0:
		mode = LUT_BYPASS;
		break;
	case 1:
		mode = LUT_RAM_A;
		break;
	case 2:
		mode = LUT_RAM_B;
		break;
	default:
		mode = LUT_BYPASS;
		break;
	}
	if (i_enable_10bits > 0)
		*is_12bits_color_channel = false;
	else
		*is_12bits_color_channel = true;

	REG_GET(CM_3DLUT_MODE, CM_3DLUT_SIZE, &lut_size);

	if (lut_size == 0)
		*is_17x17x17 = true;
	else
		*is_17x17x17 = false;

	return mode;
}