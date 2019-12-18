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
struct ov5675 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OV5675_REG_TEST_PATTERN ; 
 int /*<<< orphan*/  OV5675_REG_VALUE_08BIT ; 
 int OV5675_TEST_PATTERN_BAR_SHIFT ; 
 int OV5675_TEST_PATTERN_ENABLE ; 
 int ov5675_write_reg (struct ov5675*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ov5675_test_pattern(struct ov5675 *ov5675, u32 pattern)
{
	if (pattern)
		pattern = (pattern - 1) << OV5675_TEST_PATTERN_BAR_SHIFT |
			  OV5675_TEST_PATTERN_ENABLE;

	return ov5675_write_reg(ov5675, OV5675_REG_TEST_PATTERN,
				OV5675_REG_VALUE_08BIT, pattern);
}