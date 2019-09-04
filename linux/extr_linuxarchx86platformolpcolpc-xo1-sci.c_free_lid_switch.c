#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_lid_wake_mode ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_unregister_device (TYPE_1__*) ; 
 TYPE_1__* lid_switch_idev ; 

__attribute__((used)) static void free_lid_switch(void)
{
	device_remove_file(&lid_switch_idev->dev, &dev_attr_lid_wake_mode);
	input_unregister_device(lid_switch_idev);
}