#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usbnet {TYPE_1__* intf; int /*<<< orphan*/  data; } ;
struct huawei_cdc_ncm_state {int /*<<< orphan*/  pmcount; } ;
struct TYPE_3__ {int needs_remote_wakeup; } ;

/* Variables and functions */
 int atomic_add_return (int,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int usb_autopm_get_interface (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (TYPE_1__*) ; 

__attribute__((used)) static int huawei_cdc_ncm_manage_power(struct usbnet *usbnet_dev, int on)
{
	struct huawei_cdc_ncm_state *drvstate = (void *)&usbnet_dev->data;
	int rv;

	if ((on && atomic_add_return(1, &drvstate->pmcount) == 1) ||
			(!on && atomic_dec_and_test(&drvstate->pmcount))) {
		rv = usb_autopm_get_interface(usbnet_dev->intf);
		usbnet_dev->intf->needs_remote_wakeup = on;
		if (!rv)
			usb_autopm_put_interface(usbnet_dev->intf);
	}
	return 0;
}