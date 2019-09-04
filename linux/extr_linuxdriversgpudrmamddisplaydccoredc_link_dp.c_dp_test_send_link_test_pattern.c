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
struct TYPE_2__ {int PATTERN; int /*<<< orphan*/  DYN_RANGE; } ;
union test_misc {TYPE_1__ bits; int /*<<< orphan*/  raw; } ;
union link_test_pattern {TYPE_1__ bits; int /*<<< orphan*/  raw; } ;
struct dc_link {int dummy; } ;
typedef  enum dp_test_pattern { ____Placeholder_dp_test_pattern } dp_test_pattern ;
typedef  int /*<<< orphan*/  dpcd_test_pattern ;
typedef  int /*<<< orphan*/  dpcd_test_params ;

/* Variables and functions */
 int /*<<< orphan*/  DP_TEST_MISC0 ; 
 int /*<<< orphan*/  DP_TEST_PATTERN ; 
 int DP_TEST_PATTERN_COLOR_RAMP ; 
 int DP_TEST_PATTERN_COLOR_SQUARES ; 
 int DP_TEST_PATTERN_COLOR_SQUARES_CEA ; 
 int DP_TEST_PATTERN_VERTICAL_BARS ; 
 int DP_TEST_PATTERN_VIDEO_MODE ; 
#define  LINK_TEST_PATTERN_COLOR_RAMP 130 
#define  LINK_TEST_PATTERN_COLOR_SQUARES 129 
#define  LINK_TEST_PATTERN_VERTICAL_BARS 128 
 int /*<<< orphan*/  TEST_DYN_RANGE_VESA ; 
 int /*<<< orphan*/  core_link_read_dpcd (struct dc_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dc_link_dp_set_test_pattern (struct dc_link*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (union test_misc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dp_test_send_link_test_pattern(struct dc_link *link)
{
	union link_test_pattern dpcd_test_pattern;
	union test_misc dpcd_test_params;
	enum dp_test_pattern test_pattern;

	memset(&dpcd_test_pattern, 0, sizeof(dpcd_test_pattern));
	memset(&dpcd_test_params, 0, sizeof(dpcd_test_params));

	/* get link test pattern and pattern parameters */
	core_link_read_dpcd(
			link,
			DP_TEST_PATTERN,
			&dpcd_test_pattern.raw,
			sizeof(dpcd_test_pattern));
	core_link_read_dpcd(
			link,
			DP_TEST_MISC0,
			&dpcd_test_params.raw,
			sizeof(dpcd_test_params));

	switch (dpcd_test_pattern.bits.PATTERN) {
	case LINK_TEST_PATTERN_COLOR_RAMP:
		test_pattern = DP_TEST_PATTERN_COLOR_RAMP;
	break;
	case LINK_TEST_PATTERN_VERTICAL_BARS:
		test_pattern = DP_TEST_PATTERN_VERTICAL_BARS;
	break; /* black and white */
	case LINK_TEST_PATTERN_COLOR_SQUARES:
		test_pattern = (dpcd_test_params.bits.DYN_RANGE ==
				TEST_DYN_RANGE_VESA ?
				DP_TEST_PATTERN_COLOR_SQUARES :
				DP_TEST_PATTERN_COLOR_SQUARES_CEA);
	break;
	default:
		test_pattern = DP_TEST_PATTERN_VIDEO_MODE;
	break;
	}

	dc_link_dp_set_test_pattern(
			link,
			test_pattern,
			NULL,
			NULL,
			0);
}