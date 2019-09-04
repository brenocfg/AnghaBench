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
struct ov5645 {int /*<<< orphan*/  timing_tc_reg21; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  OV5645_SENSOR_MIRROR ; 
 int /*<<< orphan*/  OV5645_TIMING_TC_REG21 ; 
 int ov5645_write_reg (struct ov5645*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov5645_set_hflip(struct ov5645 *ov5645, s32 value)
{
	u8 val = ov5645->timing_tc_reg21;
	int ret;

	if (value == 0)
		val &= ~(OV5645_SENSOR_MIRROR);
	else
		val |= (OV5645_SENSOR_MIRROR);

	ret = ov5645_write_reg(ov5645, OV5645_TIMING_TC_REG21, val);
	if (!ret)
		ov5645->timing_tc_reg21 = val;

	return ret;
}