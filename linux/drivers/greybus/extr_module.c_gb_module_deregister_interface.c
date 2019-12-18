#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gb_interface {int disconnected; int removed; int /*<<< orphan*/  mutex; TYPE_1__* module; } ;
struct TYPE_2__ {scalar_t__ disconnected; } ;

/* Variables and functions */
 int /*<<< orphan*/  gb_interface_deactivate (struct gb_interface*) ; 
 int /*<<< orphan*/  gb_interface_del (struct gb_interface*) ; 
 int /*<<< orphan*/  gb_interface_disable (struct gb_interface*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gb_module_deregister_interface(struct gb_interface *intf)
{
	/* Mark as disconnected to prevent I/O during disable. */
	if (intf->module->disconnected)
		intf->disconnected = true;

	mutex_lock(&intf->mutex);
	intf->removed = true;
	gb_interface_disable(intf);
	gb_interface_deactivate(intf);
	mutex_unlock(&intf->mutex);

	gb_interface_del(intf);
}