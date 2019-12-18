#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_4__* psy; } ;
struct TYPE_7__ {int vbus_drop_end; } ;
struct TYPE_6__ {int charger_connected; } ;
struct ab8500_charger {int /*<<< orphan*/  charger_attached_mutex; int /*<<< orphan*/  usb_charger_attached_work; int /*<<< orphan*/  charger_wq; int /*<<< orphan*/  parent; TYPE_5__ usb_chg; TYPE_2__ flags; TYPE_1__ usb; int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_9__ {TYPE_3__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ is_ab8500 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void ab8500_charger_set_usb_connected(struct ab8500_charger *di,
	bool connected)
{
	if (connected != di->usb.charger_connected) {
		dev_dbg(di->dev, "USB connected:%i\n", connected);
		di->usb.charger_connected = connected;

		if (!connected)
			di->flags.vbus_drop_end = false;

		sysfs_notify(&di->usb_chg.psy->dev.kobj, NULL, "present");

		if (connected) {
			mutex_lock(&di->charger_attached_mutex);
			mutex_unlock(&di->charger_attached_mutex);

			if (is_ab8500(di->parent))
				queue_delayed_work(di->charger_wq,
					   &di->usb_charger_attached_work,
					   HZ);
		} else {
			cancel_delayed_work_sync(&di->usb_charger_attached_work);
			mutex_lock(&di->charger_attached_mutex);
			mutex_unlock(&di->charger_attached_mutex);
		}
	}
}