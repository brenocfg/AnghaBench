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
struct b43_wldev {int /*<<< orphan*/  list; } ;
struct b43_bus_dev {int dummy; } ;

/* Variables and functions */
 struct b43_wldev* b43_bus_get_wldev (struct b43_bus_dev*) ; 
 int /*<<< orphan*/  b43_bus_set_wldev (struct b43_bus_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  b43_debugfs_remove_device (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wireless_core_detach (struct b43_wldev*) ; 
 int /*<<< orphan*/  kfree (struct b43_wldev*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void b43_one_core_detach(struct b43_bus_dev *dev)
{
	struct b43_wldev *wldev;

	/* Do not cancel ieee80211-workqueue based work here.
	 * See comment in b43_remove(). */

	wldev = b43_bus_get_wldev(dev);
	b43_debugfs_remove_device(wldev);
	b43_wireless_core_detach(wldev);
	list_del(&wldev->list);
	b43_bus_set_wldev(dev, NULL);
	kfree(wldev);
}