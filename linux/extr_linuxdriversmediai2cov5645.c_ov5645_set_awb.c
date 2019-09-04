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
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  OV5645_AWB_MANUAL_CONTROL ; 
 int /*<<< orphan*/  OV5645_AWB_MANUAL_ENABLE ; 
 int ov5645_write_reg (struct ov5645*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov5645_set_awb(struct ov5645 *ov5645, s32 enable_auto)
{
	u8 val = 0;

	if (!enable_auto)
		val = OV5645_AWB_MANUAL_ENABLE;

	return ov5645_write_reg(ov5645, OV5645_AWB_MANUAL_CONTROL, val);
}