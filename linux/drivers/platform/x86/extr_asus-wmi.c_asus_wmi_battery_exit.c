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
struct asus_wmi {scalar_t__ battery_rsoc_available; } ;

/* Variables and functions */
 int /*<<< orphan*/  battery_hook ; 
 int /*<<< orphan*/  battery_hook_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void asus_wmi_battery_exit(struct asus_wmi *asus)
{
	if (asus->battery_rsoc_available)
		battery_hook_unregister(&battery_hook);
}