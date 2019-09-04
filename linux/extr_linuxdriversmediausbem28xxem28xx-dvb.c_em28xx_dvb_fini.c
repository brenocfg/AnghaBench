#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct em28xx_dvb {int /*<<< orphan*/  i2c_client_demod; int /*<<< orphan*/  i2c_client_tuner; int /*<<< orphan*/  i2c_client_sec; TYPE_3__** fe; } ;
struct TYPE_4__ {int /*<<< orphan*/  has_dvb; } ;
struct em28xx {int /*<<< orphan*/  ref; struct em28xx_dvb* dvb; scalar_t__ disconnected; TYPE_2__* intf; TYPE_1__ board; scalar_t__ is_audio_only; } ;
struct TYPE_6__ {void* exit; int /*<<< orphan*/  ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 void* DVB_FE_DEVICE_REMOVED ; 
 int /*<<< orphan*/  EM28XX_DIGITAL_MODE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dvb_module_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  em28xx_free_device ; 
 int /*<<< orphan*/  em28xx_uninit_usb_xfer (struct em28xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  em28xx_unregister_dvb (struct em28xx_dvb*) ; 
 int /*<<< orphan*/  kfree (struct em28xx_dvb*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prevent_sleep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int em28xx_dvb_fini(struct em28xx *dev)
{
	struct em28xx_dvb *dvb;

	if (dev->is_audio_only) {
		/* Shouldn't initialize IR for this interface */
		return 0;
	}

	if (!dev->board.has_dvb) {
		/* This device does not support the extension */
		return 0;
	}

	if (!dev->dvb)
		return 0;

	dev_info(&dev->intf->dev, "Closing DVB extension\n");

	dvb = dev->dvb;

	em28xx_uninit_usb_xfer(dev, EM28XX_DIGITAL_MODE);

	if (dev->disconnected) {
		/*
		 * We cannot tell the device to sleep
		 * once it has been unplugged.
		 */
		if (dvb->fe[0]) {
			prevent_sleep(&dvb->fe[0]->ops);
			dvb->fe[0]->exit = DVB_FE_DEVICE_REMOVED;
		}
		if (dvb->fe[1]) {
			prevent_sleep(&dvb->fe[1]->ops);
			dvb->fe[1]->exit = DVB_FE_DEVICE_REMOVED;
		}
	}

	em28xx_unregister_dvb(dvb);

	/* release I2C module bindings */
	dvb_module_release(dvb->i2c_client_sec);
	dvb_module_release(dvb->i2c_client_tuner);
	dvb_module_release(dvb->i2c_client_demod);

	kfree(dvb);
	dev->dvb = NULL;
	kref_put(&dev->ref, em28xx_free_device);

	return 0;
}