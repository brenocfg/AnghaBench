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
struct hidpp_device {int protocol_major; } ;
struct hid_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_hid (char*,char*) ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*) ; 
 struct hidpp_device* hid_get_drvdata (struct hid_device*) ; 
 char* hidpp_get_device_name (struct hidpp_device*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 

__attribute__((used)) static void hidpp_overwrite_name(struct hid_device *hdev)
{
	struct hidpp_device *hidpp = hid_get_drvdata(hdev);
	char *name;

	if (hidpp->protocol_major < 2)
		return;

	name = hidpp_get_device_name(hidpp);

	if (!name) {
		hid_err(hdev, "unable to retrieve the name of the device");
	} else {
		dbg_hid("HID++: Got name: %s\n", name);
		snprintf(hdev->name, sizeof(hdev->name), "%s", name);
	}

	kfree(name);
}