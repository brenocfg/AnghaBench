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
struct platform_device {int dummy; } ;
struct nbu2ss_udc {int linux_suspended; scalar_t__ usb_suspended; int /*<<< orphan*/  devstate; scalar_t__ vbus_active; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  USB_STATE_NOTATTACHED ; 
 int /*<<< orphan*/  _nbu2ss_disable_controller (struct nbu2ss_udc*) ; 
 int /*<<< orphan*/  _nbu2ss_quiesce (struct nbu2ss_udc*) ; 
 int /*<<< orphan*/  _nbu2ss_reset_controller (struct nbu2ss_udc*) ; 
 struct nbu2ss_udc* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int nbu2ss_drv_suspend(struct platform_device *pdev, pm_message_t state)
{
	struct nbu2ss_udc	*udc;

	udc = platform_get_drvdata(pdev);
	if (!udc)
		return 0;

	if (udc->vbus_active) {
		udc->vbus_active = 0;
		udc->devstate = USB_STATE_NOTATTACHED;
		udc->linux_suspended = 1;

		if (udc->usb_suspended) {
			udc->usb_suspended = 0;
			_nbu2ss_reset_controller(udc);
		}

		_nbu2ss_quiesce(udc);
	}
	_nbu2ss_disable_controller(udc);

	return 0;
}