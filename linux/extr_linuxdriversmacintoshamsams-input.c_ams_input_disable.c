#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * idev; } ;

/* Variables and functions */
 TYPE_1__ ams_info ; 
 int /*<<< orphan*/  input_free_polled_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_unregister_polled_device (int /*<<< orphan*/ *) ; 
 int joystick ; 

__attribute__((used)) static void ams_input_disable(void)
{
	if (ams_info.idev) {
		input_unregister_polled_device(ams_info.idev);
		input_free_polled_device(ams_info.idev);
		ams_info.idev = NULL;
	}

	joystick = false;
}