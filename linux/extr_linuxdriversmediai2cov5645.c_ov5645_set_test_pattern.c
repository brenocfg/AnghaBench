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
typedef  int /*<<< orphan*/  u8 ;
struct ov5645 {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  OV5645_PRE_ISP_TEST_SETTING_1 ; 
 int /*<<< orphan*/  OV5645_SET_TEST_PATTERN (scalar_t__) ; 
 int /*<<< orphan*/  OV5645_TEST_PATTERN_ENABLE ; 
 int ov5645_write_reg (struct ov5645*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov5645_set_test_pattern(struct ov5645 *ov5645, s32 value)
{
	u8 val = 0;

	if (value) {
		val = OV5645_SET_TEST_PATTERN(value - 1);
		val |= OV5645_TEST_PATTERN_ENABLE;
	}

	return ov5645_write_reg(ov5645, OV5645_PRE_ISP_TEST_SETTING_1, val);
}