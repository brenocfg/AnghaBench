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

/* Variables and functions */
 scalar_t__ LED_HASLCD ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 scalar_t__ lcd_no_led_support ; 
 int /*<<< orphan*/  lcd_print (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcd_text_default ; 
 int /*<<< orphan*/  led_task ; 
 scalar_t__ led_type ; 
 int /*<<< orphan*/  led_wq ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int start_task(void) 
{	
	/* Display the default text now */
	if (led_type == LED_HASLCD) lcd_print( lcd_text_default );

	/* KittyHawk has no LED support on its LCD */
	if (lcd_no_led_support) return 0;

	/* Create the work queue and queue the LED task */
	led_wq = create_singlethread_workqueue("led_wq");	
	queue_delayed_work(led_wq, &led_task, 0);

	return 0;
}