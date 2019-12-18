#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct dc_rgb* lut3; struct dc_rgb* lut2; struct dc_rgb* lut1; struct dc_rgb* lut0; } ;
struct TYPE_3__ {struct dc_rgb* lut3; struct dc_rgb* lut2; struct dc_rgb* lut1; struct dc_rgb* lut0; } ;
struct tetrahedral_params {int use_12bits; TYPE_2__ tetrahedral_9; TYPE_1__ tetrahedral_17; int /*<<< orphan*/  use_tetrahedral_9; } ;
struct dpp {int dummy; } ;
struct dc_rgb {int dummy; } ;
typedef  enum dc_lut_mode { ____Placeholder_dc_lut_mode } dc_lut_mode ;

/* Variables and functions */
 int LUT_BYPASS ; 
 int LUT_RAM_A ; 
 int LUT_RAM_B ; 
 int /*<<< orphan*/  dpp20_select_3dlut_ram (struct dpp*,int,int) ; 
 int /*<<< orphan*/  dpp20_select_3dlut_ram_mask (struct dpp*,int) ; 
 int /*<<< orphan*/  dpp20_set3dlut_ram10 (struct dpp*,struct dc_rgb*,int) ; 
 int /*<<< orphan*/  dpp20_set3dlut_ram12 (struct dpp*,struct dc_rgb*,int) ; 
 int /*<<< orphan*/  dpp20_set_3dlut_mode (struct dpp*,int,int,int) ; 
 int get3dlut_config (struct dpp*,int*,int*) ; 

bool dpp20_program_3dlut(
		struct dpp *dpp_base,
		struct tetrahedral_params *params)
{
	enum dc_lut_mode mode;
	bool is_17x17x17;
	bool is_12bits_color_channel;
	struct dc_rgb *lut0;
	struct dc_rgb *lut1;
	struct dc_rgb *lut2;
	struct dc_rgb *lut3;
	int lut_size0;
	int lut_size;

	if (params == NULL) {
		dpp20_set_3dlut_mode(dpp_base, LUT_BYPASS, false, false);
		return false;
	}
	mode = get3dlut_config(dpp_base, &is_17x17x17, &is_12bits_color_channel);

	if (mode == LUT_BYPASS || mode == LUT_RAM_B)
		mode = LUT_RAM_A;
	else
		mode = LUT_RAM_B;

	is_17x17x17 = !params->use_tetrahedral_9;
	is_12bits_color_channel = params->use_12bits;
	if (is_17x17x17) {
		lut0 = params->tetrahedral_17.lut0;
		lut1 = params->tetrahedral_17.lut1;
		lut2 = params->tetrahedral_17.lut2;
		lut3 = params->tetrahedral_17.lut3;
		lut_size0 = sizeof(params->tetrahedral_17.lut0)/
					sizeof(params->tetrahedral_17.lut0[0]);
		lut_size  = sizeof(params->tetrahedral_17.lut1)/
					sizeof(params->tetrahedral_17.lut1[0]);
	} else {
		lut0 = params->tetrahedral_9.lut0;
		lut1 = params->tetrahedral_9.lut1;
		lut2 = params->tetrahedral_9.lut2;
		lut3 = params->tetrahedral_9.lut3;
		lut_size0 = sizeof(params->tetrahedral_9.lut0)/
				sizeof(params->tetrahedral_9.lut0[0]);
		lut_size  = sizeof(params->tetrahedral_9.lut1)/
				sizeof(params->tetrahedral_9.lut1[0]);
		}

	dpp20_select_3dlut_ram(dpp_base, mode,
				is_12bits_color_channel);
	dpp20_select_3dlut_ram_mask(dpp_base, 0x1);
	if (is_12bits_color_channel)
		dpp20_set3dlut_ram12(dpp_base, lut0, lut_size0);
	else
		dpp20_set3dlut_ram10(dpp_base, lut0, lut_size0);

	dpp20_select_3dlut_ram_mask(dpp_base, 0x2);
	if (is_12bits_color_channel)
		dpp20_set3dlut_ram12(dpp_base, lut1, lut_size);
	else
		dpp20_set3dlut_ram10(dpp_base, lut1, lut_size);

	dpp20_select_3dlut_ram_mask(dpp_base, 0x4);
	if (is_12bits_color_channel)
		dpp20_set3dlut_ram12(dpp_base, lut2, lut_size);
	else
		dpp20_set3dlut_ram10(dpp_base, lut2, lut_size);

	dpp20_select_3dlut_ram_mask(dpp_base, 0x8);
	if (is_12bits_color_channel)
		dpp20_set3dlut_ram12(dpp_base, lut3, lut_size);
	else
		dpp20_set3dlut_ram10(dpp_base, lut3, lut_size);


	dpp20_set_3dlut_mode(dpp_base, mode, is_12bits_color_channel,
					is_17x17x17);

	return true;
}