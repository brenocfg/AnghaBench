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
struct usb_conn_info {scalar_t__ last_role; int /*<<< orphan*/  role_sw; int /*<<< orphan*/  vbus; int /*<<< orphan*/  dw_det; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ USB_ROLE_HOST ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct usb_conn_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_role_switch_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usb_conn_remove(struct platform_device *pdev)
{
	struct usb_conn_info *info = platform_get_drvdata(pdev);

	cancel_delayed_work_sync(&info->dw_det);

	if (info->last_role == USB_ROLE_HOST)
		regulator_disable(info->vbus);

	usb_role_switch_put(info->role_sw);

	return 0;
}