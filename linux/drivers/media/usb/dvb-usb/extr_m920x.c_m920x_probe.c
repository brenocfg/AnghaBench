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
struct usb_interface {TYPE_2__* cur_altsetting; } ;
struct usb_device_id {int dummy; } ;
struct m920x_inits {int dummy; } ;
struct dvb_usb_device {int dummy; } ;
struct TYPE_3__ {int bInterfaceNumber; } ;
struct TYPE_4__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  adapter_nr ; 
 int /*<<< orphan*/  deb (char*,int) ; 
 int /*<<< orphan*/  digivox_mini_ii_properties ; 
 int /*<<< orphan*/  dposh_properties ; 
 int dvb_usb_device_init (struct usb_interface*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct dvb_usb_device**,int /*<<< orphan*/ ) ; 
 int m920x_init (struct dvb_usb_device*,struct m920x_inits*) ; 
 int m920x_init_ep (struct usb_interface*) ; 
 int /*<<< orphan*/  megasky_properties ; 
 struct m920x_inits* megasky_rc_init ; 
 struct m920x_inits* pinnacle310e_init ; 
 int /*<<< orphan*/  pinnacle_pctv310e_properties ; 
 int /*<<< orphan*/  tvwalkertwin_properties ; 
 struct m920x_inits* tvwalkertwin_rc_init ; 
 int /*<<< orphan*/  vp7049_properties ; 
 struct m920x_inits* vp7049_rc_init ; 

__attribute__((used)) static int m920x_probe(struct usb_interface *intf,
		       const struct usb_device_id *id)
{
	struct dvb_usb_device *d = NULL;
	int ret;
	struct m920x_inits *rc_init_seq = NULL;
	int bInterfaceNumber = intf->cur_altsetting->desc.bInterfaceNumber;

	deb("Probing for m920x device at interface %d\n", bInterfaceNumber);

	if (bInterfaceNumber == 0) {
		/* Single-tuner device, or first interface on
		 * multi-tuner device
		 */

		ret = dvb_usb_device_init(intf, &megasky_properties,
					  THIS_MODULE, &d, adapter_nr);
		if (ret == 0) {
			rc_init_seq = megasky_rc_init;
			goto found;
		}

		ret = dvb_usb_device_init(intf, &digivox_mini_ii_properties,
					  THIS_MODULE, &d, adapter_nr);
		if (ret == 0) {
			/* No remote control, so no rc_init_seq */
			goto found;
		}

		/* This configures both tuners on the TV Walker Twin */
		ret = dvb_usb_device_init(intf, &tvwalkertwin_properties,
					  THIS_MODULE, &d, adapter_nr);
		if (ret == 0) {
			rc_init_seq = tvwalkertwin_rc_init;
			goto found;
		}

		ret = dvb_usb_device_init(intf, &dposh_properties,
					  THIS_MODULE, &d, adapter_nr);
		if (ret == 0) {
			/* Remote controller not supported yet. */
			goto found;
		}

		ret = dvb_usb_device_init(intf, &pinnacle_pctv310e_properties,
					  THIS_MODULE, &d, adapter_nr);
		if (ret == 0) {
			rc_init_seq = pinnacle310e_init;
			goto found;
		}

		ret = dvb_usb_device_init(intf, &vp7049_properties,
					  THIS_MODULE, &d, adapter_nr);
		if (ret == 0) {
			rc_init_seq = vp7049_rc_init;
			goto found;
		}

		return ret;
	} else {
		/* Another interface on a multi-tuner device */

		/* The LifeView TV Walker Twin gets here, but struct
		 * tvwalkertwin_properties already configured both
		 * tuners, so there is nothing for us to do here
		 */
	}

 found:
	if ((ret = m920x_init_ep(intf)) < 0)
		return ret;

	if (d && (ret = m920x_init(d, rc_init_seq)) != 0)
		return ret;

	return ret;
}