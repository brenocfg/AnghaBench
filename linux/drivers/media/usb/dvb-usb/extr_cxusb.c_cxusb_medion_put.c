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
struct cxusb_medion_dev {scalar_t__ open_type; int open_ctr; int /*<<< orphan*/  open_lock; } ;

/* Variables and functions */
 scalar_t__ CXUSB_OPEN_ANALOG ; 
 scalar_t__ CXUSB_OPEN_INIT ; 
 scalar_t__ CXUSB_OPEN_NONE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  deb_info (char*,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void cxusb_medion_put(struct dvb_usb_device *dvbdev)
{
	struct cxusb_medion_dev *cxdev = dvbdev->priv;

	mutex_lock(&cxdev->open_lock);

	if (cxdev->open_type == CXUSB_OPEN_INIT) {
		WARN_ON(cxdev->open_ctr != 0);
		cxdev->open_type = CXUSB_OPEN_NONE;
		goto unlock;
	}

	if (!WARN_ON(cxdev->open_ctr < 1)) {
		cxdev->open_ctr--;

		deb_info("release %s\n",
			 cxdev->open_type == CXUSB_OPEN_ANALOG ?
			 "analog" : "digital");
	}

unlock:
	mutex_unlock(&cxdev->open_lock);
}