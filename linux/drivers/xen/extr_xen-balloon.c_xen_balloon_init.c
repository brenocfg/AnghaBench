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
 int /*<<< orphan*/  balloon_dev ; 
 int /*<<< orphan*/  register_balloon (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  register_xenstore_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xenstore_notifier ; 

void xen_balloon_init(void)
{
	register_balloon(&balloon_dev);

	register_xenstore_notifier(&xenstore_notifier);
}