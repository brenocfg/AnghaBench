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
typedef  int /*<<< orphan*/  u32 ;
struct acpi_video_device {int /*<<< orphan*/  switch_brightness_work; int /*<<< orphan*/  switch_brightness_event; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  brightness_switch_enabled ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void brightness_switch_event(struct acpi_video_device *video_device,
				    u32 event)
{
	if (!brightness_switch_enabled)
		return;

	video_device->switch_brightness_event = event;
	schedule_delayed_work(&video_device->switch_brightness_work, HZ / 10);
}