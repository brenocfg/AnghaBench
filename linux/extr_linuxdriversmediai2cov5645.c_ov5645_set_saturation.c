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
struct ov5645 {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  OV5645_SDE_SAT_U ; 
 int /*<<< orphan*/  OV5645_SDE_SAT_V ; 
 int ov5645_write_reg (struct ov5645*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ov5645_set_saturation(struct ov5645 *ov5645, s32 value)
{
	u32 reg_value = (value * 0x10) + 0x40;
	int ret;

	ret = ov5645_write_reg(ov5645, OV5645_SDE_SAT_U, reg_value);
	if (ret < 0)
		return ret;

	return ov5645_write_reg(ov5645, OV5645_SDE_SAT_V, reg_value);
}