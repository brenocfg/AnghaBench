#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_device {int dummy; } ;
struct cx18 {int /*<<< orphan*/  sd_resetctrl; TYPE_2__* card; } ;
struct TYPE_3__ {scalar_t__ ir_reset_mask; } ;
struct TYPE_4__ {TYPE_1__ gpio_i2c_slave_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_DEBUG_INFO (char*) ; 
 int /*<<< orphan*/  CX18_GPIO_RESET_Z8F0811 ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  reset ; 
 struct cx18* to_cx18 (struct v4l2_device*) ; 
 int /*<<< orphan*/  v4l2_subdev_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cx18_reset_ir_gpio(void *data)
{
	struct cx18 *cx = to_cx18((struct v4l2_device *)data);

	if (cx->card->gpio_i2c_slave_reset.ir_reset_mask == 0)
		return;

	CX18_DEBUG_INFO("Resetting IR microcontroller\n");

	v4l2_subdev_call(&cx->sd_resetctrl,
			 core, reset, CX18_GPIO_RESET_Z8F0811);
}