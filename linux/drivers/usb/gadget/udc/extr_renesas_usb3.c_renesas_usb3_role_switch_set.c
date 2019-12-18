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
struct renesas_usb3 {scalar_t__ role_sw_by_connector; } ;
struct device {int dummy; } ;
typedef  enum usb_role { ____Placeholder_usb_role } usb_role ;

/* Variables and functions */
 struct renesas_usb3* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  handle_ext_role_switch_states (struct device*,int) ; 
 int /*<<< orphan*/  handle_role_switch_states (struct device*,int) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put (struct device*) ; 

__attribute__((used)) static int renesas_usb3_role_switch_set(struct device *dev,
					enum usb_role role)
{
	struct renesas_usb3 *usb3 = dev_get_drvdata(dev);

	pm_runtime_get_sync(dev);

	if (usb3->role_sw_by_connector)
		handle_ext_role_switch_states(dev, role);
	else
		handle_role_switch_states(dev, role);

	pm_runtime_put(dev);

	return 0;
}