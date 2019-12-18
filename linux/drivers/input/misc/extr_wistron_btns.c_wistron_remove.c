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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bios_detach () ; 
 int /*<<< orphan*/  input_free_polled_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_unregister_polled_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wistron_idev ; 
 int /*<<< orphan*/  wistron_led_remove () ; 

__attribute__((used)) static int wistron_remove(struct platform_device *dev)
{
	wistron_led_remove();
	input_unregister_polled_device(wistron_idev);
	input_free_polled_device(wistron_idev);
	bios_detach();

	return 0;
}