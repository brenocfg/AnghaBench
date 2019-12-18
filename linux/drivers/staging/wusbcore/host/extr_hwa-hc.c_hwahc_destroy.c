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
struct wusbhc {int /*<<< orphan*/  mutex; int /*<<< orphan*/  uwb_rc; int /*<<< orphan*/ * dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  usb_dev; int /*<<< orphan*/  usb_iface; } ;
struct hwahc {TYPE_1__ wa; struct wusbhc wusbhc; } ;

/* Variables and functions */
 int /*<<< orphan*/  __wa_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  hwahc_security_release (struct hwahc*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_intf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uwb_rc_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wusbhc_destroy (struct wusbhc*) ; 

__attribute__((used)) static void hwahc_destroy(struct hwahc *hwahc)
{
	struct wusbhc *wusbhc = &hwahc->wusbhc;

	mutex_lock(&wusbhc->mutex);
	__wa_destroy(&hwahc->wa);
	wusbhc_destroy(&hwahc->wusbhc);
	hwahc_security_release(hwahc);
	hwahc->wusbhc.dev = NULL;
	uwb_rc_put(wusbhc->uwb_rc);
	usb_put_intf(hwahc->wa.usb_iface);
	usb_put_dev(hwahc->wa.usb_dev);
	mutex_unlock(&wusbhc->mutex);
}