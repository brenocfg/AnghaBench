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
struct TYPE_2__ {int /*<<< orphan*/  mdev_lock; int /*<<< orphan*/ * mdev; } ;
struct dvb_usb_adapter {TYPE_1__ dvb_adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_device_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dvb_usb_media_device_unregister(struct dvb_usb_adapter *adap)
{
#ifdef CONFIG_MEDIA_CONTROLLER_DVB
	if (!adap->dvb_adap.mdev)
		return;

	mutex_lock(&adap->dvb_adap.mdev_lock);

	media_device_unregister(adap->dvb_adap.mdev);
	media_device_cleanup(adap->dvb_adap.mdev);
	kfree(adap->dvb_adap.mdev);
	adap->dvb_adap.mdev = NULL;

	mutex_unlock(&adap->dvb_adap.mdev_lock);
#endif
}