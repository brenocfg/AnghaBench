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
typedef  int u8 ;
struct hid_device {int dummy; } ;
struct gpio_chip {int dummy; } ;
struct cp2112_device {int* in_out_buffer; int /*<<< orphan*/  lock; struct hid_device* hdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP2112_GPIO_GET ; 
 int CP2112_GPIO_GET_LENGTH ; 
 int EIO ; 
 int /*<<< orphan*/  HID_FEATURE_REPORT ; 
 int /*<<< orphan*/  HID_REQ_GET_REPORT ; 
 struct cp2112_device* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*,int) ; 
 int hid_hw_raw_request (struct hid_device*,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cp2112_gpio_get_all(struct gpio_chip *chip)
{
	struct cp2112_device *dev = gpiochip_get_data(chip);
	struct hid_device *hdev = dev->hdev;
	u8 *buf = dev->in_out_buffer;
	int ret;

	mutex_lock(&dev->lock);

	ret = hid_hw_raw_request(hdev, CP2112_GPIO_GET, buf,
				 CP2112_GPIO_GET_LENGTH, HID_FEATURE_REPORT,
				 HID_REQ_GET_REPORT);
	if (ret != CP2112_GPIO_GET_LENGTH) {
		hid_err(hdev, "error requesting GPIO values: %d\n", ret);
		ret = ret < 0 ? ret : -EIO;
		goto exit;
	}

	ret = buf[1];

exit:
	mutex_unlock(&dev->lock);

	return ret;
}