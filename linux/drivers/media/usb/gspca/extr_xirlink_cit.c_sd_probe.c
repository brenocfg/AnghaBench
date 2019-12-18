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
struct usb_interface {TYPE_1__* cur_altsetting; } ;
struct usb_device_id {int driver_info; } ;
struct sd_desc {int dummy; } ;
struct sd {int dummy; } ;
struct TYPE_4__ {int bInterfaceNumber; } ;
struct TYPE_3__ {TYPE_2__ desc; } ;

/* Variables and functions */
#define  CIT_MODEL0 132 
#define  CIT_MODEL1 131 
#define  CIT_MODEL2 130 
#define  CIT_MODEL3 129 
#define  CIT_MODEL4 128 
 int ENODEV ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int gspca_dev_probe2 (struct usb_interface*,struct usb_device_id const*,struct sd_desc const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibm_netcam_pro ; 
 struct sd_desc sd_desc ; 
 struct sd_desc sd_desc_isoc_nego ; 

__attribute__((used)) static int sd_probe(struct usb_interface *intf,
			const struct usb_device_id *id)
{
	const struct sd_desc *desc = &sd_desc;

	switch (id->driver_info) {
	case CIT_MODEL0:
	case CIT_MODEL1:
		if (intf->cur_altsetting->desc.bInterfaceNumber != 2)
			return -ENODEV;
		break;
	case CIT_MODEL2:
	case CIT_MODEL4:
		if (intf->cur_altsetting->desc.bInterfaceNumber != 0)
			return -ENODEV;
		break;
	case CIT_MODEL3:
		if (intf->cur_altsetting->desc.bInterfaceNumber != 0)
			return -ENODEV;
		/* FIXME this likely applies to all model3 cams and probably
		   to other models too. */
		if (ibm_netcam_pro)
			desc = &sd_desc_isoc_nego;
		break;
	}

	return gspca_dev_probe2(intf, id, desc, sizeof(struct sd), THIS_MODULE);
}