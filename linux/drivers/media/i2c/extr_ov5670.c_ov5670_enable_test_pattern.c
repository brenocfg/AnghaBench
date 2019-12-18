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
typedef  scalar_t__ u32 ;
struct ov5670 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OV5670_REG_TEST_PATTERN ; 
 int /*<<< orphan*/  OV5670_REG_TEST_PATTERN_CTRL ; 
 int /*<<< orphan*/  OV5670_REG_VALUE_08BIT ; 
 scalar_t__ OV5670_TEST_PATTERN_ENABLE ; 
 int ov5670_read_reg (struct ov5670*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int ov5670_write_reg (struct ov5670*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ov5670_enable_test_pattern(struct ov5670 *ov5670, u32 pattern)
{
	u32 val;
	int ret;

	/* Set the bayer order that we support */
	ret = ov5670_write_reg(ov5670, OV5670_REG_TEST_PATTERN_CTRL,
			       OV5670_REG_VALUE_08BIT, 0);
	if (ret)
		return ret;

	ret = ov5670_read_reg(ov5670, OV5670_REG_TEST_PATTERN,
			      OV5670_REG_VALUE_08BIT, &val);
	if (ret)
		return ret;

	if (pattern)
		val |= OV5670_TEST_PATTERN_ENABLE;
	else
		val &= ~OV5670_TEST_PATTERN_ENABLE;

	return ov5670_write_reg(ov5670, OV5670_REG_TEST_PATTERN,
				OV5670_REG_VALUE_08BIT, val);
}