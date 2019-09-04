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
typedef  int u8 ;
struct stk1160 {size_t ctl_input; int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int const*) ; 
 int SAA7115_COMPOSITE0 ; 
 int SAA7115_SVIDEO3 ; 
 int /*<<< orphan*/  STK1160_GCTRL ; 
 size_t STK1160_SVIDEO_INPUT ; 
 int /*<<< orphan*/  s_routing ; 
 int /*<<< orphan*/  stk1160_write_reg (struct stk1160*,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  v4l2_device_call_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video ; 

void stk1160_select_input(struct stk1160 *dev)
{
	int route;
	static const u8 gctrl[] = {
		0x98, 0x90, 0x88, 0x80, 0x98
	};

	if (dev->ctl_input == STK1160_SVIDEO_INPUT)
		route = SAA7115_SVIDEO3;
	else
		route = SAA7115_COMPOSITE0;

	if (dev->ctl_input < ARRAY_SIZE(gctrl)) {
		v4l2_device_call_all(&dev->v4l2_dev, 0, video, s_routing,
				route, 0, 0);
		stk1160_write_reg(dev, STK1160_GCTRL, gctrl[dev->ctl_input]);
	}
}