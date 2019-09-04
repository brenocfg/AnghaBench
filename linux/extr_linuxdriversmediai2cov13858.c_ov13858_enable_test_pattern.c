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
typedef  int u32 ;
struct ov13858 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OV13858_REG_TEST_PATTERN ; 
 int /*<<< orphan*/  OV13858_REG_VALUE_08BIT ; 
 int OV13858_TEST_PATTERN_ENABLE ; 
 int OV13858_TEST_PATTERN_MASK ; 
 int ov13858_read_reg (struct ov13858*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int ov13858_write_reg (struct ov13858*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ov13858_enable_test_pattern(struct ov13858 *ov13858, u32 pattern)
{
	int ret;
	u32 val;

	ret = ov13858_read_reg(ov13858, OV13858_REG_TEST_PATTERN,
			       OV13858_REG_VALUE_08BIT, &val);
	if (ret)
		return ret;

	if (pattern) {
		val &= OV13858_TEST_PATTERN_MASK;
		val |= (pattern - 1) | OV13858_TEST_PATTERN_ENABLE;
	} else {
		val &= ~OV13858_TEST_PATTERN_ENABLE;
	}

	return ov13858_write_reg(ov13858, OV13858_REG_TEST_PATTERN,
				 OV13858_REG_VALUE_08BIT, val);
}