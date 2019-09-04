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
typedef  void* u8 ;
struct led_classdev {TYPE_1__* dev; } ;
struct hid_device {int dummy; } ;
struct elan_drvdata {void* mute_led_state; } ;
struct device {int dummy; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;
struct TYPE_2__ {struct device* parent; } ;

/* Variables and functions */
 int ELAN_LED_REPORT_SIZE ; 
 unsigned char ELAN_MUTE_LED_REPORT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HID_FEATURE_REPORT ; 
 int /*<<< orphan*/  HID_REQ_SET_REPORT ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*,int) ; 
 struct elan_drvdata* hid_get_drvdata (struct hid_device*) ; 
 int hid_hw_raw_request (struct hid_device*,unsigned char,unsigned char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct hid_device* to_hid_device (struct device*) ; 

__attribute__((used)) static int elan_mute_led_set_brigtness(struct led_classdev *led_cdev,
				       enum led_brightness value)
{
	int ret;
	u8 led_state;
	struct device *dev = led_cdev->dev->parent;
	struct hid_device *hdev = to_hid_device(dev);
	struct elan_drvdata *drvdata = hid_get_drvdata(hdev);

	unsigned char *dmabuf = kzalloc(ELAN_LED_REPORT_SIZE, GFP_KERNEL);

	if (!dmabuf)
		return -ENOMEM;

	led_state = !!value;

	dmabuf[0] = ELAN_MUTE_LED_REPORT;
	dmabuf[1] = 0x02;
	dmabuf[2] = led_state;

	ret = hid_hw_raw_request(hdev, dmabuf[0], dmabuf, ELAN_LED_REPORT_SIZE,
				 HID_FEATURE_REPORT, HID_REQ_SET_REPORT);

	kfree(dmabuf);

	if (ret != ELAN_LED_REPORT_SIZE) {
		hid_err(hdev, "Failed to set mute led brightness: %d\n", ret);
		return ret;
	}

	drvdata->mute_led_state = led_state;
	return 0;
}