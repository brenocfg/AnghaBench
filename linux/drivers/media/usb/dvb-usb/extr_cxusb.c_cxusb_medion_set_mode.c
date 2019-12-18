#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct dvb_usb_device {int /*<<< orphan*/  i2c_mutex; TYPE_1__* udev; struct cxusb_state* priv; } ;
struct cxusb_state {int* gpio_write_refresh; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  CMD_ANALOG ; 
 int /*<<< orphan*/  CMD_DIGITAL ; 
 int cxusb_ctrl_msg (struct dvb_usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usb_clear_halt (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (TYPE_1__*,int) ; 
 int usb_set_interface (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (TYPE_1__*,int) ; 

__attribute__((used)) static int cxusb_medion_set_mode(struct dvb_usb_device *dvbdev, bool digital)
{
	struct cxusb_state *st = dvbdev->priv;
	int ret;
	u8 b;
	unsigned int i;

	/*
	 * switching mode while doing an I2C transaction often causes
	 * the device to crash
	 */
	mutex_lock(&dvbdev->i2c_mutex);

	if (digital) {
		ret = usb_set_interface(dvbdev->udev, 0, 6);
		if (ret != 0) {
			dev_err(&dvbdev->udev->dev,
				"digital interface selection failed (%d)\n",
				ret);
			goto ret_unlock;
		}
	} else {
		ret = usb_set_interface(dvbdev->udev, 0, 1);
		if (ret != 0) {
			dev_err(&dvbdev->udev->dev,
				"analog interface selection failed (%d)\n",
				ret);
			goto ret_unlock;
		}
	}

	/* pipes need to be cleared after setting interface */
	ret = usb_clear_halt(dvbdev->udev, usb_rcvbulkpipe(dvbdev->udev, 1));
	if (ret != 0)
		dev_warn(&dvbdev->udev->dev,
			 "clear halt on IN pipe failed (%d)\n",
			 ret);

	ret = usb_clear_halt(dvbdev->udev, usb_sndbulkpipe(dvbdev->udev, 1));
	if (ret != 0)
		dev_warn(&dvbdev->udev->dev,
			 "clear halt on OUT pipe failed (%d)\n",
			 ret);

	ret = cxusb_ctrl_msg(dvbdev, digital ? CMD_DIGITAL : CMD_ANALOG,
			     NULL, 0, &b, 1);
	if (ret != 0) {
		dev_err(&dvbdev->udev->dev, "mode switch failed (%d)\n",
			ret);
		goto ret_unlock;
	}

	/* mode switch seems to reset GPIO states */
	for (i = 0; i < ARRAY_SIZE(st->gpio_write_refresh); i++)
		st->gpio_write_refresh[i] = true;

ret_unlock:
	mutex_unlock(&dvbdev->i2c_mutex);

	return ret;
}