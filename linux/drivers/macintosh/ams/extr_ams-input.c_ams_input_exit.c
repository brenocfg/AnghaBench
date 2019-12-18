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
 int /*<<< orphan*/  ams_input_disable () ; 
 int /*<<< orphan*/  ams_input_mutex ; 
 int /*<<< orphan*/  dev_attr_joystick ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void ams_input_exit(void)
{
	device_remove_file(&ams_info.of_dev->dev, &dev_attr_joystick);

	mutex_lock(&ams_input_mutex);
	ams_input_disable();
	mutex_unlock(&ams_input_mutex);
}