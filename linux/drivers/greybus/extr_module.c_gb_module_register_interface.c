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
typedef  int /*<<< orphan*/  u8 ;
struct gb_module {int /*<<< orphan*/  dev; } ;
struct gb_interface {scalar_t__ type; int /*<<< orphan*/  mutex; int /*<<< orphan*/  interface_id; struct gb_module* module; } ;

/* Variables and functions */
 scalar_t__ GB_INTERFACE_TYPE_DUMMY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int gb_interface_activate (struct gb_interface*) ; 
 int gb_interface_add (struct gb_interface*) ; 
 int /*<<< orphan*/  gb_interface_deactivate (struct gb_interface*) ; 
 int gb_interface_enable (struct gb_interface*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gb_module_register_interface(struct gb_interface *intf)
{
	struct gb_module *module = intf->module;
	u8 intf_id = intf->interface_id;
	int ret;

	mutex_lock(&intf->mutex);

	ret = gb_interface_activate(intf);
	if (ret) {
		if (intf->type != GB_INTERFACE_TYPE_DUMMY) {
			dev_err(&module->dev,
				"failed to activate interface %u: %d\n",
				intf_id, ret);
		}

		gb_interface_add(intf);
		goto err_unlock;
	}

	ret = gb_interface_add(intf);
	if (ret)
		goto err_interface_deactivate;

	ret = gb_interface_enable(intf);
	if (ret) {
		dev_err(&module->dev, "failed to enable interface %u: %d\n",
			intf_id, ret);
		goto err_interface_deactivate;
	}

	mutex_unlock(&intf->mutex);

	return;

err_interface_deactivate:
	gb_interface_deactivate(intf);
err_unlock:
	mutex_unlock(&intf->mutex);
}