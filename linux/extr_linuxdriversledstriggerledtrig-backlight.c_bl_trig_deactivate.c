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
struct led_classdev {int dummy; } ;
struct bl_trig_notifier {int /*<<< orphan*/  notifier; } ;

/* Variables and functions */
 int /*<<< orphan*/  fb_unregister_client (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct bl_trig_notifier*) ; 
 struct bl_trig_notifier* led_get_trigger_data (struct led_classdev*) ; 

__attribute__((used)) static void bl_trig_deactivate(struct led_classdev *led)
{
	struct bl_trig_notifier *n = led_get_trigger_data(led);

	fb_unregister_client(&n->notifier);
	kfree(n);
}