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
struct kobj_uevent_env {int dummy; } ;
struct gb_svc {struct gb_host_device* hd; } ;
struct gb_module {int /*<<< orphan*/  module_id; struct gb_host_device* hd; } ;
struct gb_interface {int /*<<< orphan*/  product_id; int /*<<< orphan*/  vendor_id; int /*<<< orphan*/  interface_id; struct gb_host_device* hd; struct gb_module* module; } ;
struct gb_host_device {int /*<<< orphan*/  bus_id; } ;
struct gb_control {struct gb_interface* intf; } ;
struct gb_bundle {int /*<<< orphan*/  class; int /*<<< orphan*/  id; struct gb_interface* intf; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ add_uevent_var (struct kobj_uevent_env*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dev_WARN (struct device*,char*) ; 
 scalar_t__ is_gb_bundle (struct device*) ; 
 scalar_t__ is_gb_control (struct device*) ; 
 scalar_t__ is_gb_host_device (struct device*) ; 
 scalar_t__ is_gb_interface (struct device*) ; 
 scalar_t__ is_gb_module (struct device*) ; 
 scalar_t__ is_gb_svc (struct device*) ; 
 struct gb_bundle* to_gb_bundle (struct device*) ; 
 struct gb_control* to_gb_control (struct device*) ; 
 struct gb_host_device* to_gb_host_device (struct device*) ; 
 struct gb_interface* to_gb_interface (struct device*) ; 
 struct gb_module* to_gb_module (struct device*) ; 
 struct gb_svc* to_gb_svc (struct device*) ; 

__attribute__((used)) static int greybus_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	struct gb_host_device *hd;
	struct gb_module *module = NULL;
	struct gb_interface *intf = NULL;
	struct gb_control *control = NULL;
	struct gb_bundle *bundle = NULL;
	struct gb_svc *svc = NULL;

	if (is_gb_host_device(dev)) {
		hd = to_gb_host_device(dev);
	} else if (is_gb_module(dev)) {
		module = to_gb_module(dev);
		hd = module->hd;
	} else if (is_gb_interface(dev)) {
		intf = to_gb_interface(dev);
		module = intf->module;
		hd = intf->hd;
	} else if (is_gb_control(dev)) {
		control = to_gb_control(dev);
		intf = control->intf;
		module = intf->module;
		hd = intf->hd;
	} else if (is_gb_bundle(dev)) {
		bundle = to_gb_bundle(dev);
		intf = bundle->intf;
		module = intf->module;
		hd = intf->hd;
	} else if (is_gb_svc(dev)) {
		svc = to_gb_svc(dev);
		hd = svc->hd;
	} else {
		dev_WARN(dev, "uevent for unknown greybus device \"type\"!\n");
		return -EINVAL;
	}

	if (add_uevent_var(env, "BUS=%u", hd->bus_id))
		return -ENOMEM;

	if (module) {
		if (add_uevent_var(env, "MODULE=%u", module->module_id))
			return -ENOMEM;
	}

	if (intf) {
		if (add_uevent_var(env, "INTERFACE=%u", intf->interface_id))
			return -ENOMEM;
		if (add_uevent_var(env, "GREYBUS_ID=%08x/%08x",
				   intf->vendor_id, intf->product_id))
			return -ENOMEM;
	}

	if (bundle) {
		// FIXME
		// add a uevent that can "load" a bundle type
		// This is what we need to bind a driver to so use the info
		// in gmod here as well

		if (add_uevent_var(env, "BUNDLE=%u", bundle->id))
			return -ENOMEM;
		if (add_uevent_var(env, "BUNDLE_CLASS=%02x", bundle->class))
			return -ENOMEM;
	}

	return 0;
}