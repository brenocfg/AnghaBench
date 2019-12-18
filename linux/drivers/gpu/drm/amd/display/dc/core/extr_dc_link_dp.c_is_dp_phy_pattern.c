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
typedef  enum dp_test_pattern { ____Placeholder_dp_test_pattern } dp_test_pattern ;

/* Variables and functions */
 int DP_TEST_PATTERN_PHY_PATTERN_BEGIN ; 
 int DP_TEST_PATTERN_PHY_PATTERN_END ; 
 int DP_TEST_PATTERN_VIDEO_MODE ; 

__attribute__((used)) static bool is_dp_phy_pattern(enum dp_test_pattern test_pattern)
{
	if ((DP_TEST_PATTERN_PHY_PATTERN_BEGIN <= test_pattern &&
			test_pattern <= DP_TEST_PATTERN_PHY_PATTERN_END) ||
			test_pattern == DP_TEST_PATTERN_VIDEO_MODE)
		return true;
	else
		return false;
}