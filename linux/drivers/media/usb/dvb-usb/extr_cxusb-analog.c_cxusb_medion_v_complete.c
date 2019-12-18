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
struct urb {struct dvb_usb_device* context; } ;
struct dvb_usb_device {TYPE_1__* udev; struct cxusb_medion_dev* priv; } ;
struct cxusb_medion_dev {int /*<<< orphan*/  urbwork; int /*<<< orphan*/  urbcomplete; struct urb** streamurbs; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int CXUSB_VIDEO_URBS ; 
 int /*<<< orphan*/  URB ; 
 int /*<<< orphan*/  cxusb_vprintk (struct dvb_usb_device*,int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cxusb_medion_v_complete(struct urb *u)
{
	struct dvb_usb_device *dvbdev = u->context;
	struct cxusb_medion_dev *cxdev = dvbdev->priv;
	unsigned int i;

	for (i = 0; i < CXUSB_VIDEO_URBS; i++)
		if (cxdev->streamurbs[i] == u)
			break;

	if (i >= CXUSB_VIDEO_URBS) {
		dev_err(&dvbdev->udev->dev,
			"complete on unknown URB\n");
		return;
	}

	cxusb_vprintk(dvbdev, URB, "URB %u complete\n", i);

	set_bit(i, &cxdev->urbcomplete);
	schedule_work(&cxdev->urbwork);
}