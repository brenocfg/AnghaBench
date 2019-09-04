#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  (* close ) (TYPE_1__*) ;} ;
struct TYPE_4__ {TYPE_1__ dmx; } ;
struct dvb_usb_adapter {int state; int /*<<< orphan*/  dvb_adap; TYPE_2__ demux; int /*<<< orphan*/  dmxdev; int /*<<< orphan*/  dvb_net; } ;

/* Variables and functions */
 int DVB_USB_ADAP_STATE_DVB ; 
 int /*<<< orphan*/  deb_info (char*) ; 
 int /*<<< orphan*/  dvb_dmx_release (TYPE_2__*) ; 
 int /*<<< orphan*/  dvb_dmxdev_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_net_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_unregister_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_usb_media_device_unregister (struct dvb_usb_adapter*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

int dvb_usb_adapter_dvb_exit(struct dvb_usb_adapter *adap)
{
	if (adap->state & DVB_USB_ADAP_STATE_DVB) {
		deb_info("unregistering DVB part\n");
		dvb_net_release(&adap->dvb_net);
		adap->demux.dmx.close(&adap->demux.dmx);
		dvb_dmxdev_release(&adap->dmxdev);
		dvb_dmx_release(&adap->demux);
		dvb_usb_media_device_unregister(adap);
		dvb_unregister_adapter(&adap->dvb_adap);
		adap->state &= ~DVB_USB_ADAP_STATE_DVB;
	}
	return 0;
}