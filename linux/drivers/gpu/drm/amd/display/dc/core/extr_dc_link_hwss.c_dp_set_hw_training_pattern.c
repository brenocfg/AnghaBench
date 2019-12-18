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
struct dc_link {int dummy; } ;
typedef  enum dp_test_pattern { ____Placeholder_dp_test_pattern } dp_test_pattern ;
typedef  enum dc_dp_training_pattern { ____Placeholder_dc_dp_training_pattern } dc_dp_training_pattern ;

/* Variables and functions */
 int DP_TEST_PATTERN_TRAINING_PATTERN1 ; 
 int DP_TEST_PATTERN_TRAINING_PATTERN2 ; 
 int DP_TEST_PATTERN_TRAINING_PATTERN3 ; 
 int DP_TEST_PATTERN_TRAINING_PATTERN4 ; 
 int DP_TEST_PATTERN_UNSUPPORTED ; 
#define  DP_TRAINING_PATTERN_SEQUENCE_1 131 
#define  DP_TRAINING_PATTERN_SEQUENCE_2 130 
#define  DP_TRAINING_PATTERN_SEQUENCE_3 129 
#define  DP_TRAINING_PATTERN_SEQUENCE_4 128 
 int /*<<< orphan*/  dp_set_hw_test_pattern (struct dc_link*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool dp_set_hw_training_pattern(
	struct dc_link *link,
	enum dc_dp_training_pattern pattern)
{
	enum dp_test_pattern test_pattern = DP_TEST_PATTERN_UNSUPPORTED;

	switch (pattern) {
	case DP_TRAINING_PATTERN_SEQUENCE_1:
		test_pattern = DP_TEST_PATTERN_TRAINING_PATTERN1;
		break;
	case DP_TRAINING_PATTERN_SEQUENCE_2:
		test_pattern = DP_TEST_PATTERN_TRAINING_PATTERN2;
		break;
	case DP_TRAINING_PATTERN_SEQUENCE_3:
		test_pattern = DP_TEST_PATTERN_TRAINING_PATTERN3;
		break;
	case DP_TRAINING_PATTERN_SEQUENCE_4:
		test_pattern = DP_TEST_PATTERN_TRAINING_PATTERN4;
		break;
	default:
		break;
	}

	dp_set_hw_test_pattern(link, test_pattern, NULL, 0);

	return true;
}