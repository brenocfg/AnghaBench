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
struct TYPE_4__ {TYPE_1__* devices; } ;
struct dvb_usb_device {struct cxusb_medion_dev* priv; TYPE_2__ props; } ;
struct cxusb_medion_dev {scalar_t__ open_type; int /*<<< orphan*/  open_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/ ** warm_ids; } ;

/* Variables and functions */
 scalar_t__ CXUSB_OPEN_ANALOG ; 
 int EBUSY ; 
 size_t MEDION_MD95700 ; 
 int _cxusb_power_ctrl (struct dvb_usb_device*,int) ; 
 int /*<<< orphan*/ * cxusb_table ; 
 int /*<<< orphan*/  deb_info (char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cxusb_power_ctrl(struct dvb_usb_device *d, int onoff)
{
	bool is_medion = d->props.devices[0].warm_ids[0] == &cxusb_table[MEDION_MD95700];
	int ret;

	if (is_medion && !onoff) {
		struct cxusb_medion_dev *cxdev = d->priv;

		mutex_lock(&cxdev->open_lock);

		if (cxdev->open_type == CXUSB_OPEN_ANALOG) {
			deb_info("preventing DVB core from setting power OFF while we are in analog mode\n");
			ret = -EBUSY;
			goto ret_unlock;
		}
	}

	ret = _cxusb_power_ctrl(d, onoff);

ret_unlock:
	if (is_medion && !onoff) {
		struct cxusb_medion_dev *cxdev = d->priv;

		mutex_unlock(&cxdev->open_lock);
	}

	return ret;
}