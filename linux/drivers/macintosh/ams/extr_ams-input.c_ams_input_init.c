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
struct TYPE_4__ {TYPE_1__* of_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 TYPE_2__ ams_info ; 
 int /*<<< orphan*/  ams_input_enable () ; 
 int /*<<< orphan*/  dev_attr_joystick ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ joystick ; 

int ams_input_init(void)
{
	if (joystick)
		ams_input_enable();

	return device_create_file(&ams_info.of_dev->dev, &dev_attr_joystick);
}