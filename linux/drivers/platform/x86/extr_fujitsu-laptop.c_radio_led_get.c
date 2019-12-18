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
struct led_classdev {TYPE_1__* dev; } ;
struct acpi_device {int dummy; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUNC_FLAGS ; 
 int LED_FULL ; 
 int LED_OFF ; 
 int RADIO_LED_ON ; 
 int call_fext_func (struct acpi_device*,int /*<<< orphan*/ ,int,int,int) ; 
 struct acpi_device* to_acpi_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum led_brightness radio_led_get(struct led_classdev *cdev)
{
	struct acpi_device *device = to_acpi_device(cdev->dev->parent);
	enum led_brightness brightness = LED_OFF;

	if (call_fext_func(device, FUNC_FLAGS, 0x4, 0x0, 0x0) & RADIO_LED_ON)
		brightness = LED_FULL;

	return brightness;
}