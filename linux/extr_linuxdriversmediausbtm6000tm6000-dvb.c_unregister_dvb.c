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
struct urb {int /*<<< orphan*/ * transfer_buffer; } ;
struct tm6000_dvb {int /*<<< orphan*/  mutex; int /*<<< orphan*/  adapter; int /*<<< orphan*/  demux; int /*<<< orphan*/  dmxdev; scalar_t__ frontend; struct urb* bulk_urb; } ;
struct tm6000_core {struct tm6000_dvb* dvb; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvb_dmx_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_dmxdev_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_frontend_detach (scalar_t__) ; 
 int /*<<< orphan*/  dvb_unregister_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_unregister_frontend (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_unlink_urb (struct urb*) ; 

__attribute__((used)) static void unregister_dvb(struct tm6000_core *dev)
{
	struct tm6000_dvb *dvb = dev->dvb;

	if (dvb->bulk_urb) {
		struct urb *bulk_urb = dvb->bulk_urb;

		kfree(bulk_urb->transfer_buffer);
		bulk_urb->transfer_buffer = NULL;
		usb_unlink_urb(bulk_urb);
		usb_free_urb(bulk_urb);
	}

/*	mutex_lock(&tm6000_driver.open_close_mutex); */
	if (dvb->frontend) {
		dvb_unregister_frontend(dvb->frontend);
		dvb_frontend_detach(dvb->frontend);
	}

	dvb_dmxdev_release(&dvb->dmxdev);
	dvb_dmx_release(&dvb->demux);
	dvb_unregister_adapter(&dvb->adapter);
	mutex_destroy(&dvb->mutex);
/*	mutex_unlock(&tm6000_driver.open_close_mutex); */
}