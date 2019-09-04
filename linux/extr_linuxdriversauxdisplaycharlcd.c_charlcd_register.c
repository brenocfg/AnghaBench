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
struct charlcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  charlcd_dev ; 
 int charlcd_init (struct charlcd*) ; 
 int misc_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panel_notifier ; 
 int /*<<< orphan*/  register_reboot_notifier (int /*<<< orphan*/ *) ; 
 struct charlcd* the_charlcd ; 

int charlcd_register(struct charlcd *lcd)
{
	int ret;

	ret = charlcd_init(lcd);
	if (ret)
		return ret;

	ret = misc_register(&charlcd_dev);
	if (ret)
		return ret;

	the_charlcd = lcd;
	register_reboot_notifier(&panel_notifier);
	return 0;
}