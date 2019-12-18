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
struct TYPE_2__ {int* pointer; } ;
union acpi_object {scalar_t__ type; TYPE_1__ buffer; } ;
struct led_classdev {int dummy; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;

/* Variables and functions */
 scalar_t__ ACPI_TYPE_BUFFER ; 
 int LED_FULL ; 
 int LED_HALF ; 
 int LED_OFF ; 
 int /*<<< orphan*/  WM_GET ; 
 int /*<<< orphan*/  WM_KEY_LIGHT ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 
 union acpi_object* lg_wmab (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum led_brightness kbd_backlight_get(struct led_classdev *cdev)
{
	union acpi_object *r;
	int val;

	r = lg_wmab(WM_KEY_LIGHT, WM_GET, 0);

	if (!r)
		return LED_OFF;

	if (r->type != ACPI_TYPE_BUFFER || r->buffer.pointer[1] != 0x05) {
		kfree(r);
		return LED_OFF;
	}

	switch (r->buffer.pointer[0] & 0x27) {
	case 0x24:
		val = LED_FULL;
		break;
	case 0x22:
		val = LED_HALF;
		break;
	default:
		val = LED_OFF;
	}

	kfree(r);

	return val;
}