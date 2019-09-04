#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dvb_usb_device {int num_adapters_initialized; int /*<<< orphan*/  state; TYPE_1__* adapter; } ;
struct TYPE_4__ {int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DVB_USB_STATE_DVB ; 
 int /*<<< orphan*/  dvb_usb_adapter_dvb_exit (TYPE_1__*) ; 
 int /*<<< orphan*/  dvb_usb_adapter_frontend_exit (TYPE_1__*) ; 
 int /*<<< orphan*/  dvb_usb_adapter_stream_exit (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dvb_usb_adapter_exit(struct dvb_usb_device *d)
{
	int n;

	for (n = 0; n < d->num_adapters_initialized; n++) {
		dvb_usb_adapter_frontend_exit(&d->adapter[n]);
		dvb_usb_adapter_dvb_exit(&d->adapter[n]);
		dvb_usb_adapter_stream_exit(&d->adapter[n]);
		kfree(d->adapter[n].priv);
	}
	d->num_adapters_initialized = 0;
	d->state &= ~DVB_USB_STATE_DVB;
	return 0;
}