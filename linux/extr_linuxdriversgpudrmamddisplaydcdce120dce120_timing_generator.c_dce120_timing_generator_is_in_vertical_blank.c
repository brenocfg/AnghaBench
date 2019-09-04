#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct timing_generator {int /*<<< orphan*/  ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  crtc; } ;
struct dce110_timing_generator {TYPE_1__ offsets; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC0_CRTC_STATUS ; 
 int /*<<< orphan*/  CRTC_V_BLANK ; 
 struct dce110_timing_generator* DCE110TG_FROM_TG (struct timing_generator*) ; 
 int dm_read_reg_soc15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_reg_field_value (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCRTC0_CRTC_STATUS ; 

__attribute__((used)) static bool dce120_timing_generator_is_in_vertical_blank(
		struct timing_generator *tg)
{
	uint32_t field = 0;
	struct dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uint32_t value = dm_read_reg_soc15(
					tg->ctx,
					mmCRTC0_CRTC_STATUS,
					tg110->offsets.crtc);

	field = get_reg_field_value(value, CRTC0_CRTC_STATUS, CRTC_V_BLANK);
	return field == 1;
}