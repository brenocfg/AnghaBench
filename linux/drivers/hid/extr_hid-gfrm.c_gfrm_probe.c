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
struct hid_device_id {scalar_t__ driver_data; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ GFRM100 ; 
 int /*<<< orphan*/  GFRM100_SEARCH_KEY_REPORT_ID ; 
 int /*<<< orphan*/  HID_CONNECT_DEFAULT ; 
 int /*<<< orphan*/  HID_INPUT_REPORT ; 
 int hid_hw_start (struct hid_device*,int /*<<< orphan*/ ) ; 
 int hid_parse (struct hid_device*) ; 
 int /*<<< orphan*/  hid_register_report (struct hid_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_set_drvdata (struct hid_device*,void*) ; 

__attribute__((used)) static int gfrm_probe(struct hid_device *hdev, const struct hid_device_id *id)
{
	int ret;

	hid_set_drvdata(hdev, (void *) id->driver_data);

	ret = hid_parse(hdev);
	if (ret)
		goto done;

	if (id->driver_data == GFRM100) {
		/*
		 * GFRM100 HID Report Descriptor does not describe the Search
		 * key reports. Thus, we need to add it manually here, so that
		 * those reports reach gfrm_raw_event() from hid_input_report().
		 */
		if (!hid_register_report(hdev, HID_INPUT_REPORT,
					 GFRM100_SEARCH_KEY_REPORT_ID, 0)) {
			ret = -ENOMEM;
			goto done;
		}
	}

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
done:
	return ret;
}