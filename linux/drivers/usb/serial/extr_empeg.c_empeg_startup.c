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
struct usb_serial {TYPE_3__* dev; } ;
struct TYPE_6__ {TYPE_2__* actconfig; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int bConfigurationValue; } ;
struct TYPE_5__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int usb_reset_configuration (TYPE_3__*) ; 

__attribute__((used)) static int empeg_startup(struct usb_serial *serial)
{
	int r;

	if (serial->dev->actconfig->desc.bConfigurationValue != 1) {
		dev_err(&serial->dev->dev, "active config #%d != 1 ??\n",
			serial->dev->actconfig->desc.bConfigurationValue);
		return -ENODEV;
	}

	r = usb_reset_configuration(serial->dev);

	/* continue on with initialization */
	return r;
}