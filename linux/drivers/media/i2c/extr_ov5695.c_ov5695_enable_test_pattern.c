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
struct ov5695 {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  OV5695_REG_TEST_PATTERN ; 
 int /*<<< orphan*/  OV5695_REG_VALUE_08BIT ; 
 int OV5695_TEST_PATTERN_DISABLE ; 
 int OV5695_TEST_PATTERN_ENABLE ; 
 int ov5695_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ov5695_enable_test_pattern(struct ov5695 *ov5695, u32 pattern)
{
	u32 val;

	if (pattern)
		val = (pattern - 1) | OV5695_TEST_PATTERN_ENABLE;
	else
		val = OV5695_TEST_PATTERN_DISABLE;

	return ov5695_write_reg(ov5695->client, OV5695_REG_TEST_PATTERN,
				OV5695_REG_VALUE_08BIT, val);
}