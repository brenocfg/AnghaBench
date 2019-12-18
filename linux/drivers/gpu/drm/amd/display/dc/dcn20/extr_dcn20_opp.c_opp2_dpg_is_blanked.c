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
struct output_pixel_processor {int dummy; } ;
struct dcn20_opp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPG_CONTROL ; 
 int /*<<< orphan*/  DPG_DOUBLE_BUFFER_PENDING ; 
 int /*<<< orphan*/  DPG_EN ; 
 int /*<<< orphan*/  DPG_MODE ; 
 int /*<<< orphan*/  DPG_STATUS ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  REG_GET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int*) ; 
 struct dcn20_opp* TO_DCN20_OPP (struct output_pixel_processor*) ; 

bool opp2_dpg_is_blanked(struct output_pixel_processor *opp)
{
	struct dcn20_opp *oppn20 = TO_DCN20_OPP(opp);
	uint32_t dpg_en, dpg_mode;
	uint32_t double_buffer_pending;

	REG_GET_2(DPG_CONTROL,
			DPG_EN, &dpg_en,
			DPG_MODE, &dpg_mode);

	REG_GET(DPG_STATUS,
			DPG_DOUBLE_BUFFER_PENDING, &double_buffer_pending);

	return (dpg_en == 1) &&
		(double_buffer_pending == 0);
}