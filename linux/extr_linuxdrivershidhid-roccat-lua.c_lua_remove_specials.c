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
struct usb_interface {int dummy; } ;
struct lua_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct hid_device {TYPE_1__ dev; } ;

/* Variables and functions */
 struct lua_device* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  kfree (struct lua_device*) ; 
 int /*<<< orphan*/  lua_remove_sysfs_attributes (struct usb_interface*) ; 
 struct usb_interface* to_usb_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lua_remove_specials(struct hid_device *hdev)
{
	struct usb_interface *intf = to_usb_interface(hdev->dev.parent);
	struct lua_device *lua;

	lua_remove_sysfs_attributes(intf);

	lua = hid_get_drvdata(hdev);
	kfree(lua);
}