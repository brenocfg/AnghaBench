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
struct dc_rgb {int red; int green; int blue; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_3DLUT_DATA ; 
 int /*<<< orphan*/  CM_3DLUT_DATA0 ; 
 int /*<<< orphan*/  CM_3DLUT_DATA1 ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 struct dcn20_dpp* TO_DCN20_DPP (struct dpp*) ; 

__attribute__((used)) static void dpp20_set3dlut_ram12(
		struct dpp *dpp_base,
		const struct dc_rgb *lut,
		uint32_t entries)
{
	uint32_t i, red, green, blue, red1, green1, blue1;
	struct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	for (i = 0 ; i < entries; i += 2) {
		red   = lut[i].red<<4;
		green = lut[i].green<<4;
		blue  = lut[i].blue<<4;
		red1   = lut[i+1].red<<4;
		green1 = lut[i+1].green<<4;
		blue1  = lut[i+1].blue<<4;

		REG_SET_2(CM_3DLUT_DATA, 0,
				CM_3DLUT_DATA0, red,
				CM_3DLUT_DATA1, red1);

		REG_SET_2(CM_3DLUT_DATA, 0,
				CM_3DLUT_DATA0, green,
				CM_3DLUT_DATA1, green1);

		REG_SET_2(CM_3DLUT_DATA, 0,
				CM_3DLUT_DATA0, blue,
				CM_3DLUT_DATA1, blue1);

	}
}