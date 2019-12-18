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
struct wtp_data {int /*<<< orphan*/  mt_feature_index; int /*<<< orphan*/  x_size; } ;
struct hidpp_device {struct wtp_data* private_data; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hid_err (struct hid_device*,char*,int) ; 
 struct hidpp_device* hid_get_drvdata (struct hid_device*) ; 
 int hidpp_touchpad_set_raw_report_state (struct hidpp_device*,int /*<<< orphan*/ ,int,int) ; 
 int wtp_get_config (struct hidpp_device*) ; 

__attribute__((used)) static int wtp_connect(struct hid_device *hdev, bool connected)
{
	struct hidpp_device *hidpp = hid_get_drvdata(hdev);
	struct wtp_data *wd = hidpp->private_data;
	int ret;

	if (!wd->x_size) {
		ret = wtp_get_config(hidpp);
		if (ret) {
			hid_err(hdev, "Can not get wtp config: %d\n", ret);
			return ret;
		}
	}

	return hidpp_touchpad_set_raw_report_state(hidpp, wd->mt_feature_index,
			true, true);
}