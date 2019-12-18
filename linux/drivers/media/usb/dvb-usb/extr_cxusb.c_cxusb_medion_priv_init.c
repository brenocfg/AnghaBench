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
struct dvb_usb_device {struct cxusb_medion_dev* priv; } ;
struct cxusb_medion_dev {int /*<<< orphan*/  open_lock; int /*<<< orphan*/  open_type; struct dvb_usb_device* dvbdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXUSB_OPEN_INIT ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cxusb_medion_priv_init(struct dvb_usb_device *dvbdev)
{
	struct cxusb_medion_dev *cxdev = dvbdev->priv;

	cxdev->dvbdev = dvbdev;
	cxdev->open_type = CXUSB_OPEN_INIT;
	mutex_init(&cxdev->open_lock);

	return 0;
}