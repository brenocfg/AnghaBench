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
typedef  int /*<<< orphan*/  u8 ;
struct wacom {int /*<<< orphan*/  lock; } ;
struct hid_device {scalar_t__ bus; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ BUS_BLUETOOTH ; 
 int EINVAL ; 
 int /*<<< orphan*/  WAC_CMD_ICON_BT_XFER ; 
 int /*<<< orphan*/  WAC_CMD_ICON_XFER ; 
 struct wacom* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct hid_device* to_hid_device (struct device*) ; 
 int wacom_led_putimage (struct wacom*,int,int /*<<< orphan*/ ,unsigned int,char const*) ; 

__attribute__((used)) static ssize_t wacom_button_image_store(struct device *dev, int button_id,
					const char *buf, size_t count)
{
	struct hid_device *hdev = to_hid_device(dev);
	struct wacom *wacom = hid_get_drvdata(hdev);
	int err;
	unsigned len;
	u8 xfer_id;

	if (hdev->bus == BUS_BLUETOOTH) {
		len = 256;
		xfer_id = WAC_CMD_ICON_BT_XFER;
	} else {
		len = 1024;
		xfer_id = WAC_CMD_ICON_XFER;
	}

	if (count != len)
		return -EINVAL;

	mutex_lock(&wacom->lock);

	err = wacom_led_putimage(wacom, button_id, xfer_id, len, buf);

	mutex_unlock(&wacom->lock);

	return err < 0 ? err : count;
}