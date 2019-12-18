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
typedef  union acpi_object {int dummy; } acpi_object ;
struct led_classdev {int dummy; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;

/* Variables and functions */
 int LED_OFF ; 
 int /*<<< orphan*/  WM_SET ; 
 int /*<<< orphan*/  WM_TLED ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 
 union acpi_object* lg_wmab (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tpad_led_set(struct led_classdev *cdev,
			 enum led_brightness brightness)
{
	union acpi_object *r;

	r = lg_wmab(WM_TLED, WM_SET, brightness > LED_OFF);
	kfree(r);
}