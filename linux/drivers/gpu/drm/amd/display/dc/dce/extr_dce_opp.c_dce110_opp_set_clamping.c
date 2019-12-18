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
struct dce110_opp {int dummy; } ;
struct clamping_and_pixel_encoding_params {int clamping_level; } ;

/* Variables and functions */
#define  CLAMPING_FULL_RANGE 132 
#define  CLAMPING_LIMITED_RANGE_10BPC 131 
#define  CLAMPING_LIMITED_RANGE_12BPC 130 
#define  CLAMPING_LIMITED_RANGE_8BPC 129 
#define  CLAMPING_LIMITED_RANGE_PROGRAMMABLE 128 
 int /*<<< orphan*/  FMT_CLAMP_CNTL ; 
 int /*<<< orphan*/  FMT_CLAMP_COLOR_FORMAT ; 
 int /*<<< orphan*/  FMT_CLAMP_COMPONENT_B ; 
 int /*<<< orphan*/  FMT_CLAMP_COMPONENT_G ; 
 int /*<<< orphan*/  FMT_CLAMP_COMPONENT_R ; 
 int /*<<< orphan*/  FMT_CLAMP_DATA_EN ; 
 int /*<<< orphan*/  FMT_CLAMP_LOWER_B ; 
 int /*<<< orphan*/  FMT_CLAMP_LOWER_G ; 
 int /*<<< orphan*/  FMT_CLAMP_LOWER_R ; 
 int /*<<< orphan*/  FMT_CLAMP_UPPER_B ; 
 int /*<<< orphan*/  FMT_CLAMP_UPPER_G ; 
 int /*<<< orphan*/  FMT_CLAMP_UPPER_R ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

void dce110_opp_set_clamping(
	struct dce110_opp *opp110,
	const struct clamping_and_pixel_encoding_params *params)
{
	REG_SET_2(FMT_CLAMP_CNTL, 0,
		FMT_CLAMP_DATA_EN, 0,
		FMT_CLAMP_COLOR_FORMAT, 0);

	switch (params->clamping_level) {
	case CLAMPING_FULL_RANGE:
		break;
	case CLAMPING_LIMITED_RANGE_8BPC:
		REG_SET_2(FMT_CLAMP_CNTL, 0,
			FMT_CLAMP_DATA_EN, 1,
			FMT_CLAMP_COLOR_FORMAT, 1);
		break;
	case CLAMPING_LIMITED_RANGE_10BPC:
		REG_SET_2(FMT_CLAMP_CNTL, 0,
			FMT_CLAMP_DATA_EN, 1,
			FMT_CLAMP_COLOR_FORMAT, 2);
		break;
	case CLAMPING_LIMITED_RANGE_12BPC:
		REG_SET_2(FMT_CLAMP_CNTL, 0,
			FMT_CLAMP_DATA_EN, 1,
			FMT_CLAMP_COLOR_FORMAT, 3);
		break;
	case CLAMPING_LIMITED_RANGE_PROGRAMMABLE:
		/*Set clamp control*/
		REG_SET_2(FMT_CLAMP_CNTL, 0,
			FMT_CLAMP_DATA_EN, 1,
			FMT_CLAMP_COLOR_FORMAT, 7);

		/*set the defaults*/
		REG_SET_2(FMT_CLAMP_COMPONENT_R, 0,
			FMT_CLAMP_LOWER_R, 0x10,
			FMT_CLAMP_UPPER_R, 0xFEF);

		REG_SET_2(FMT_CLAMP_COMPONENT_G, 0,
			FMT_CLAMP_LOWER_G, 0x10,
			FMT_CLAMP_UPPER_G, 0xFEF);

		REG_SET_2(FMT_CLAMP_COMPONENT_B, 0,
			FMT_CLAMP_LOWER_B, 0x10,
			FMT_CLAMP_UPPER_B, 0xFEF);
		break;
	default:
		break;
	}
}