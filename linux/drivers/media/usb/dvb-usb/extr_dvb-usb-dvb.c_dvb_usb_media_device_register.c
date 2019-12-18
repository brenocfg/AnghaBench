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
struct TYPE_2__ {int /*<<< orphan*/  mdev; } ;
struct dvb_usb_adapter {TYPE_1__ dvb_adap; } ;

/* Variables and functions */
 int media_device_register (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int  dvb_usb_media_device_register(struct dvb_usb_adapter *adap)
{
#ifdef CONFIG_MEDIA_CONTROLLER_DVB
	return media_device_register(adap->dvb_adap.mdev);
#else
	return 0;
#endif
}