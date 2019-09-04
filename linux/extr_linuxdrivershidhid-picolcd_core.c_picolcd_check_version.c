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
struct picolcd_pending {int raw_size; int /*<<< orphan*/ * raw_data; } ;
struct picolcd_data {int status; int /*<<< orphan*/ * version; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int PICOLCD_BOOTLOADER ; 
 int /*<<< orphan*/  REPORT_VERSION ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*) ; 
 struct picolcd_data* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  hid_info (struct hid_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct picolcd_pending*) ; 
 struct picolcd_pending* picolcd_send_and_wait (struct hid_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int picolcd_check_version(struct hid_device *hdev)
{
	struct picolcd_data *data = hid_get_drvdata(hdev);
	struct picolcd_pending *verinfo;
	int ret = 0;

	if (!data)
		return -ENODEV;

	verinfo = picolcd_send_and_wait(hdev, REPORT_VERSION, NULL, 0);
	if (!verinfo) {
		hid_err(hdev, "no version response from PicoLCD\n");
		return -ENODEV;
	}

	if (verinfo->raw_size == 2) {
		data->version[0] = verinfo->raw_data[1];
		data->version[1] = verinfo->raw_data[0];
		if (data->status & PICOLCD_BOOTLOADER) {
			hid_info(hdev, "PicoLCD, bootloader version %d.%d\n",
				 verinfo->raw_data[1], verinfo->raw_data[0]);
		} else {
			hid_info(hdev, "PicoLCD, firmware version %d.%d\n",
				 verinfo->raw_data[1], verinfo->raw_data[0]);
		}
	} else {
		hid_err(hdev, "confused, got unexpected version response from PicoLCD\n");
		ret = -EINVAL;
	}
	kfree(verinfo);
	return ret;
}