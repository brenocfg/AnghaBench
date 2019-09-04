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
struct ov7251 {int /*<<< orphan*/  pre_isp_00; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  OV7251_PRE_ISP_00 ; 
 int /*<<< orphan*/  OV7251_PRE_ISP_00_TEST_PATTERN ; 
 int ov7251_write_reg (struct ov7251*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov7251_set_test_pattern(struct ov7251 *ov7251, s32 value)
{
	u8 val = ov7251->pre_isp_00;
	int ret;

	if (value)
		val |= OV7251_PRE_ISP_00_TEST_PATTERN;
	else
		val &= ~OV7251_PRE_ISP_00_TEST_PATTERN;

	ret = ov7251_write_reg(ov7251, OV7251_PRE_ISP_00, val);
	if (!ret)
		ov7251->pre_isp_00 = val;

	return ret;
}