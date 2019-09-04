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
struct steam_device {scalar_t__* serial_no; int /*<<< orphan*/  list; int /*<<< orphan*/  hdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  hid_info (int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  steam_battery_unregister (struct steam_device*) ; 
 int /*<<< orphan*/  steam_devices_lock ; 
 int /*<<< orphan*/  steam_input_unregister (struct steam_device*) ; 

__attribute__((used)) static void steam_unregister(struct steam_device *steam)
{
	steam_battery_unregister(steam);
	steam_input_unregister(steam);
	if (steam->serial_no[0]) {
		hid_info(steam->hdev, "Steam Controller '%s' disconnected",
				steam->serial_no);
		mutex_lock(&steam_devices_lock);
		list_del(&steam->list);
		mutex_unlock(&steam_devices_lock);
		steam->serial_no[0] = 0;
	}
}