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
typedef  int u64 ;
struct hid_report {int dummy; } ;
struct hid_device {int dummy; } ;
struct creative_sb0540 {int /*<<< orphan*/  input_dev; } ;

/* Variables and functions */
 int KEY_RESERVED ; 
 int get_key (struct creative_sb0540*,int) ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*,int) ; 
 struct creative_sb0540* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int reverse (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int creative_sb0540_raw_event(struct hid_device *hid,
	struct hid_report *report, u8 *data, int len)
{
	struct creative_sb0540 *creative_sb0540 = hid_get_drvdata(hid);
	u64 code, main_code;
	int key;

	if (len != 6)
		return 0;

	/* From daemons/hw_hiddev.c sb0540_rec() in lirc */
	code = reverse(data[5], 8);
	main_code = (code << 8) + ((~code) & 0xff);

	/*
	 * Flip to get values in the same format as
	 * remotes/creative/lircd.conf.alsa_usb in lirc
	 */
	main_code = ((main_code & 0xff) << 8) +
		((main_code & 0xff00) >> 8);

	key = get_key(creative_sb0540, main_code);
	if (key == 0 || key == KEY_RESERVED) {
		hid_err(hid, "Could not get a key for main_code %llX\n",
			main_code);
		return 0;
	}

	input_report_key(creative_sb0540->input_dev, key, 1);
	input_report_key(creative_sb0540->input_dev, key, 0);
	input_sync(creative_sb0540->input_dev);

	/* let hidraw and hiddev handle the report */
	return 0;
}