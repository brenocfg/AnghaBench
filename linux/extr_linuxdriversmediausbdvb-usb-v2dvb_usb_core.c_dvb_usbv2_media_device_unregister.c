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
struct dvb_usb_adapter {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void dvb_usbv2_media_device_unregister(struct dvb_usb_adapter *adap)
{
#ifdef CONFIG_MEDIA_CONTROLLER_DVB

	if (!adap->dvb_adap.mdev)
		return;

	media_device_unregister(adap->dvb_adap.mdev);
	media_device_cleanup(adap->dvb_adap.mdev);
	kfree(adap->dvb_adap.mdev);
	adap->dvb_adap.mdev = NULL;

#endif
}