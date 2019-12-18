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
struct hid_device_id {int dummy; } ;
struct hid_device {int /*<<< orphan*/  quirks; int /*<<< orphan*/  dev; } ;
struct creative_sb0540 {struct hid_device* hid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HID_CONNECT_DEFAULT ; 
 int /*<<< orphan*/  HID_QUIRK_HIDINPUT_FORCE ; 
 struct creative_sb0540* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*) ; 
 int hid_hw_start (struct hid_device*,int /*<<< orphan*/ ) ; 
 int hid_parse (struct hid_device*) ; 
 int /*<<< orphan*/  hid_set_drvdata (struct hid_device*,struct creative_sb0540*) ; 

__attribute__((used)) static int creative_sb0540_probe(struct hid_device *hid,
		const struct hid_device_id *id)
{
	int ret;
	struct creative_sb0540 *creative_sb0540;

	creative_sb0540 = devm_kzalloc(&hid->dev,
		sizeof(struct creative_sb0540), GFP_KERNEL);

	if (!creative_sb0540)
		return -ENOMEM;

	creative_sb0540->hid = hid;

	/* force input as some remotes bypass the input registration */
	hid->quirks |= HID_QUIRK_HIDINPUT_FORCE;

	hid_set_drvdata(hid, creative_sb0540);

	ret = hid_parse(hid);
	if (ret) {
		hid_err(hid, "parse failed\n");
		return ret;
	}

	ret = hid_hw_start(hid, HID_CONNECT_DEFAULT);
	if (ret) {
		hid_err(hid, "hw start failed\n");
		return ret;
	}

	return ret;
}