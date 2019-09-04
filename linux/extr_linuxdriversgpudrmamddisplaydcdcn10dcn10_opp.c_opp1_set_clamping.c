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
struct dcn10_opp {int dummy; } ;
struct clamping_and_pixel_encoding_params {int clamping_level; } ;

/* Variables and functions */
#define  CLAMPING_FULL_RANGE 132 
#define  CLAMPING_LIMITED_RANGE_10BPC 131 
#define  CLAMPING_LIMITED_RANGE_12BPC 130 
#define  CLAMPING_LIMITED_RANGE_8BPC 129 
#define  CLAMPING_LIMITED_RANGE_PROGRAMMABLE 128 
 int /*<<< orphan*/  FMT_CLAMP_CNTL ; 
 int /*<<< orphan*/  FMT_CLAMP_COLOR_FORMAT ; 
 int /*<<< orphan*/  FMT_CLAMP_DATA_EN ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void opp1_set_clamping(
	struct dcn10_opp *oppn10,
	const struct clamping_and_pixel_encoding_params *params)
{
	REG_UPDATE_2(FMT_CLAMP_CNTL,
			FMT_CLAMP_DATA_EN, 0,
			FMT_CLAMP_COLOR_FORMAT, 0);

	switch (params->clamping_level) {
	case CLAMPING_FULL_RANGE:
		REG_UPDATE_2(FMT_CLAMP_CNTL,
				FMT_CLAMP_DATA_EN, 1,
				FMT_CLAMP_COLOR_FORMAT, 0);
		break;
	case CLAMPING_LIMITED_RANGE_8BPC:
		REG_UPDATE_2(FMT_CLAMP_CNTL,
				FMT_CLAMP_DATA_EN, 1,
				FMT_CLAMP_COLOR_FORMAT, 1);
		break;
	case CLAMPING_LIMITED_RANGE_10BPC:
		REG_UPDATE_2(FMT_CLAMP_CNTL,
				FMT_CLAMP_DATA_EN, 1,
				FMT_CLAMP_COLOR_FORMAT, 2);

		break;
	case CLAMPING_LIMITED_RANGE_12BPC:
		REG_UPDATE_2(FMT_CLAMP_CNTL,
				FMT_CLAMP_DATA_EN, 1,
				FMT_CLAMP_COLOR_FORMAT, 3);
		break;
	case CLAMPING_LIMITED_RANGE_PROGRAMMABLE:
		/* TODO */
	default:
		break;
	}

}