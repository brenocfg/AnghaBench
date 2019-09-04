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
struct work_struct {int dummy; } ;

/* Variables and functions */
 scalar_t__ acpi_backlight_video ; 
 scalar_t__ acpi_video_get_backlight_type () ; 
 int /*<<< orphan*/  acpi_video_unregister_backlight () ; 

__attribute__((used)) static void acpi_video_backlight_notify_work(struct work_struct *work)
{
	if (acpi_video_get_backlight_type() != acpi_backlight_video)
		acpi_video_unregister_backlight();
}