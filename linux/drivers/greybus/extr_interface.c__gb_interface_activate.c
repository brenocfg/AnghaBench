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
struct gb_interface {int active; scalar_t__ removed; scalar_t__ ejected; } ;
typedef  enum gb_interface_type { ____Placeholder_gb_interface_type } gb_interface_type ;

/* Variables and functions */
 int ENODEV ; 
#define  GB_INTERFACE_TYPE_GREYBUS 129 
#define  GB_INTERFACE_TYPE_UNIPRO 128 
 int GB_INTERFACE_TYPE_UNKNOWN ; 
 int gb_interface_activate_operation (struct gb_interface*,int*) ; 
 int /*<<< orphan*/  gb_interface_hibernate_link (struct gb_interface*) ; 
 int gb_interface_read_dme (struct gb_interface*) ; 
 int gb_interface_refclk_set (struct gb_interface*,int) ; 
 int gb_interface_route_create (struct gb_interface*) ; 
 int gb_interface_unipro_set (struct gb_interface*,int) ; 
 int gb_interface_vsys_set (struct gb_interface*,int) ; 
 int /*<<< orphan*/  trace_gb_interface_activate (struct gb_interface*) ; 

__attribute__((used)) static int _gb_interface_activate(struct gb_interface *intf,
				  enum gb_interface_type *type)
{
	int ret;

	*type = GB_INTERFACE_TYPE_UNKNOWN;

	if (intf->ejected || intf->removed)
		return -ENODEV;

	ret = gb_interface_vsys_set(intf, true);
	if (ret)
		return ret;

	ret = gb_interface_refclk_set(intf, true);
	if (ret)
		goto err_vsys_disable;

	ret = gb_interface_unipro_set(intf, true);
	if (ret)
		goto err_refclk_disable;

	ret = gb_interface_activate_operation(intf, type);
	if (ret) {
		switch (*type) {
		case GB_INTERFACE_TYPE_UNIPRO:
		case GB_INTERFACE_TYPE_GREYBUS:
			goto err_hibernate_link;
		default:
			goto err_unipro_disable;
		}
	}

	ret = gb_interface_read_dme(intf);
	if (ret)
		goto err_hibernate_link;

	ret = gb_interface_route_create(intf);
	if (ret)
		goto err_hibernate_link;

	intf->active = true;

	trace_gb_interface_activate(intf);

	return 0;

err_hibernate_link:
	gb_interface_hibernate_link(intf);
err_unipro_disable:
	gb_interface_unipro_set(intf, false);
err_refclk_disable:
	gb_interface_refclk_set(intf, false);
err_vsys_disable:
	gb_interface_vsys_set(intf, false);

	return ret;
}