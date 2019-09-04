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
struct wm8350_led {int /*<<< orphan*/  value; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_OFF ; 
 struct wm8350_led* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  wm8350_led_disable (struct wm8350_led*) ; 

__attribute__((used)) static void wm8350_led_shutdown(struct platform_device *pdev)
{
	struct wm8350_led *led = platform_get_drvdata(pdev);

	led->value = LED_OFF;
	wm8350_led_disable(led);
}